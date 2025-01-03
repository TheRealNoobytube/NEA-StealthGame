#pragma once
#include "Source/Application/Data Structures/List.h"
#include <variant>

class Animation {
private:
	struct AbsractTrack {
		virtual ~AbsractTrack() = default;
		std::string type;
	};

	List<AbsractTrack*> tracks;

public:
	template <typename T>
	class Track : public AbsractTrack {
	private:
		struct Key {
			Key(float time = 0, T value = NULL) : time(time), value(value) {} //constructer shorthand
			float time;
			T value;
		};

		List<Key> keys;

	public:
		T* obj;

		Track(T* obj) {
			this->obj = obj;
		}
		~Track() {}

		int insertKey(float time, T newValue) {
			keys.add(Key(time, newValue));
			return keys.getSize();
		}

		void changeKeyValue(int index, T newValue, float time = -1) {
			Key key = keys.get(index);
			key.value = newValue;
			if (time >= 0) {
				key.time = time;
			}
		}

		void removeKey(int index) {
			keys.remove(index);
		}
	};

	float length = 1;
	std::string name;
	bool loop = false;

	Animation(std::string name) {
		this->name = name;
	}

	template <typename T>
	Track<T>* createTrack(T* trackVariable) {
		Track<T>* track = new Track(trackVariable);

		//dynamic_cast<typename>(track);
		//track->type = typeid(T);
		tracks.add(track);
		return track;
	}

	template <typename T>
	Track<T>* getTrack(int index) {
		auto track = tracks.get(index);
		return track;
	}
	

};