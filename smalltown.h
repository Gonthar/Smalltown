/*
 * smalltown.h
 *
 *  Created on: 26 lis 2016
 *      Author: mg277344
 */

#ifndef SMALLTOWN_H
#define SMALLTOWN_H

#include <tuple>
#include <vector>

template<size_t N> struct Fib {
    enum { value = Fib<N-1>::value + Fib<N-2>::value };
};
template<> struct Fib<1> { enum { value = 1 }; };
template<> struct Fib<0> { enum { value = 1 }; };

template <typename M, typename U, U t0, U t1, typename... C>
class SmallTown {

    private:

        M monster_;
        U attackStarts_, dayEnds_;
        size_t citizensStillAlive_;
        std::vector<size_t> attackHours_;
        std::tuple<C...> citizens_;

        bool isMonsterDead() const {
            return monster_.getHealth() == 0;
        }
/*
        void getResult() {
            if (isMonsterDead()) {
                if (citizensStillAlive_ == 0) {
                    std::cout << "DRAW\n";
                }
                else {
                    std::cout << "CITIZENS WON\n";
                }
            }
            else if (citizensStillAlive_ == 0) {
                std::cout << "MONSTER WON\n";
            }
        }

        void attackAll() {
            attackHelper<0, C...>();
        }

        template<size_t N>
        void singleAttack() {
            auto &citizen = std::get<N>(citizens_);
            if (citizen.getHealth() > 0) {
                attack(monster_, citizen);
                if (citizen.getHealth() == 0) {
                    --citizensStillAlive_;
                }
            }
        }

        template<int>
        void attackHelper() {}

        template<int, typename Arg, typename...Args>
        void attackHelper() {
            attackHelper<0, Args...>();
            singleAttack<sizeof...(Args)>();
        }

        */
///

        static std::vector<size_t> determineAttacks() {
            size_t max = 0;
            std::vector<size_t> v;
            while(Fib<max>::value < t1) {
                v.push_back(Fib<max>::value);
                ++max;
            }
            return v;
        }

    public:
        SmallTown(M const &monster, C... citizens,
                typename std::enable_if<std::is_arithmetic<U>::value>::type * = 0) :
                monster_(monster), attackStarts_(t0), dayEnds_(t1), citizens_(citizens...) {
            citizensStillAlive_ = sizeof...(citizens);
            attackHours_ = determineAttacks;
        }


        std::tuple<std::string, typename M::valueType, size_t> getStatus() {
            return std::make_tuple(getMonsterType(monster_),
                monster_.getHealth(), citizensStillAlive_);
        }

        void tick(U timeStep) {
            //getResult();
            // Fibonacci
            //attackAll();
            attackStarts_ += timeStep;
        }
};
///
// nie jestem pewien, czy to dziala
template<typename T>
std::string getMonsterType(T t) { return ""; }

template<typename T, const char* NAME>
std::string getMonsterType(Monster<T, NAME> monster) {
    return monster.getMonsterType();
}


#endif //SMALLTOWN_H

