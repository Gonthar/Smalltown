/*
 * monster.h
 *
 *  Created on: 26 lis 2016
 *      Author: mg277344
 */

#ifndef MONSTER_H
#define MONSTER_H

#include <typeinfo>
#include <algorithm>
#include <string>
#include <cassert>
#include <type_traits>

//enum MonsterType { mummy, vampire, zombie }; ?

template<typename T, const char* MonsterType, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Monster {

    private:

        T health_, attackPower_;

    public:

        Monster(T hp, T ap) :
    	health_(hp), attackPower_(ap) {
    		assert(hp > 0);
    		assert(ap >= 0);
        }

    	T getHealth() const { return health_; }

    	T getAttackPower() const { return attackPower_; }

        const char* getMonsterType() const { return MonsterType; }

    	void takeDamage(T damage) {
    		assert(damage >= 0);
    		health_ -= std::min(health_, damage);
    	}
};
const char ZOMBIE_NAME[] = "Zombie";
const char MUMMY_NAME[] = "Mummy";
const char VAMPIRE_NAME[] = "Vampire";

template<typename T>
using Zombie = Monster<T, ZOMBIE_NAME>;

template<typename T>
using Mummy = Monster<T, MUMMY_NAME>;

template<typename T>
using Vampire = Monster<T, VAMPIRE_NAME>;



template<typename A, typename V>
void attack(A &attacker, V &victim) {
    victim.takeDamage(attacker.getAttackPower());
}

template<typename A, typename D>
void attack(A &attacker, Sheriff<D> &defender) {
	defender.takeDamage(attacker.getAttackPower());
    attacker.takeDamage(defender.getAttackPower());
}

#endif /* MONSTER_H */
