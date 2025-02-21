#include "Raycast.h"

Raycast::Raycast(std::string name) : Collision(name) {

}


void Raycast::ready() {
    __super::ready();
}

void Raycast::update(float delta) {
    __super::update(delta);
    Vector2D globalPosition = getGlobalPosition();

    forceUpdateRaycast();

    if (visible) {
        if (isColliding()) {
            drawLine(globalPosition, Vector2D(globalPosition.x + targetPosition.x, globalPosition.y + targetPosition.y), Color(50, 180, 10));
            drawRect(intersectionPoint, Vector2D(1, 1), Color(0, 255, 255));
        }
        else {
            drawLine(globalPosition, Vector2D(globalPosition.x + targetPosition.x, globalPosition.y + targetPosition.y), Color(255, 0, 0));
        }
    }
}

bool Raycast::checkForIntersections(Node* node) {
    bool intersectionFound = false;

    bool nodeIsValidBody = false;
    auto body = dynamic_cast<CollisionBody*>(node);

    if ((!ignoreParent || node != getParent()) && body != nullptr) {
        nodeIsValidBody = true;
    }

    if (nodeIsValidBody) {
        if (body->layer & (mask)) {
            for (int i = 0; i < body->getChildCount(); i++) {
                auto shape = dynamic_cast<CollisionRect*>(body->getChild(i));

                if (shape != nullptr) {
                    intersectionFound = findRectIntersections(shape);
                }
            }
        }
    }

    for (int i = 0; i < node->getChildCount(); i++) {
        if (checkForIntersections(node->getChild(i))) {
            intersectionFound = true;
        }
    }

    return intersectionFound;
}


bool Raycast::findRectIntersections(CollisionRect* rect) {
    Vector2D globalPosition = getGlobalPosition();
    Vector2D shapeGlobalPosition = rect->getGlobalPosition();

    //the target position is considered the direction of the ray and is used as such

    Vector2D tNear = Vector2D(shapeGlobalPosition.x - globalPosition.x, shapeGlobalPosition.y - globalPosition.y);
    tNear.x /= targetPosition.x;
    tNear.y /= targetPosition.y;

    Vector2D tFar = Vector2D(shapeGlobalPosition.x + rect->getSize().x - globalPosition.x, shapeGlobalPosition.y + rect->getSize().y - globalPosition.y);
    tFar.x /= targetPosition.x;
    tFar.y /= targetPosition.y;


    if (std::isnan(tFar.x) || std::isnan(tFar.y)) {
        return false;
    }

    if (std::isnan(tNear.x) || std::isnan(tNear.y)){
        return false;
    }


    if (tNear.x > tFar.x) {
        std::swap(tNear.x, tFar.x);
    }
    if (tNear.y > tFar.y) {
        std::swap(tNear.y, tFar.y);
    }


    if (tNear.x > tFar.y || tNear.y > tFar.x) {
        return false;
    }


    float tHitFar = std::min(tFar.x, tFar.y);

    if (tHitFar < 0) {
        return false;
    }

    contactTime = std::max(tNear.x, tNear.y);

    if (contactTime < 0 || contactTime >= 1) {
        return false;
    }


    intersectionPoint = globalPosition;
    intersectionPoint.x += contactTime * targetPosition.x;
    intersectionPoint.y += contactTime * targetPosition.y;

    if (tNear.x > tNear.y) {
        if (1 / targetPosition.x < 0) {
            //intersecting right side of rectangle
            contactNormal = Vector2D(1, 0);
        }
        else {
            //intersecting left side of rectangle
            contactNormal = Vector2D(-1, 0);
        }
    }
    else if (tNear.x < tNear.y){
        if (1 / targetPosition.y < 0) {
            //intersecting bottom side of rectangle
            contactNormal = Vector2D(0, 1);
        }
        else {
            //intersecting top side of rectangle
            contactNormal = Vector2D(0, -1);
        }
    }


    return true;
}



void Raycast::forceUpdateRaycast() {
    resetValues();
    colliding = checkForIntersections(getSceneTree()->getRoot());
}

void Raycast::checkAgainstRect(CollisionRect* rect) {
    resetValues();
    colliding = findRectIntersections(rect);

    if (!colliding) {
        if (rect->point_rectIsColliding(getGlobalPosition())) {

            colliding = true;
            contactNormal = Vector2D(1, 1);
            contactTime = 1;
            intersectionPoint = getGlobalPosition();
        }
    }
}


void Raycast::resetValues() {
    intersectionPoint = Vector2D(INFINITY, INFINITY);
    contactNormal = Vector2D(0, 0);
    contactTime = INFINITY;
}


bool Raycast::isColliding() {
    return colliding;
}

Vector2D Raycast::getIntersectionPoint() {
    return intersectionPoint;
}

Vector2D Raycast::getContactNormal() {
    return contactNormal;
}

