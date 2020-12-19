// ConsoleApplication43.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <functional>

namespace NetworkSimulation {
    bool And(bool a, bool b) {
        return a && b;
    }

    bool Or(bool a, bool b) {
        return a || b;
    }

    bool NotAnd(bool a, bool b) {
        return !(a && b);
    }

    bool NotOr(bool a, bool b) {
        return !(a || b);
    }

    bool ExOr(bool a, bool b) {
        return ((a && !b) || (b && !a));
    }

    const std::vector<std::function<bool(bool, bool)>> funcList{ And, Or, NotAnd, NotOr, ExOr };

    struct Signal {
        bool slot1;
        bool slot2;
        bool slot3;
        bool slot4;
    };

    struct Network {
        std::function<bool(bool, bool)> f1;
        std::function<bool(bool, bool)> f2;
        std::function<bool(bool, bool)> f3;
        Network(std::function<bool(bool, bool)> _f1,
            std::function<bool(bool, bool)> _f2,
            std::function<bool(bool, bool)> _f3) :f1{ _f1 }, f2{ _f2 }, f3{ _f3 }{}
        bool Calculate(bool a, bool b, bool c, bool d) {
            return f3(f1(a, b), f2(c, d));
        }
    };

    std::tuple<unsigned short, unsigned short, unsigned short> Solve(std::vector<Signal> _sigv, std::vector<bool> _resv) {
        std::tuple<unsigned short, unsigned short, unsigned short> res = std::make_tuple(0, 0, 0);
        auto max_index = (_sigv.size() > _resv.size()) ? (_resv.size()) : (_sigv.size());
        for (unsigned short i1 = 0; i1 < 5; ++i1) {
            for (unsigned short i2 = 0; i2 < 5; ++i2) {
                for (unsigned short i3 = 0; i3 < 5; ++i3) {
                    Network baust(funcList[i1], funcList[i2], funcList[i3]);
                    std::vector<bool> diff(max_index);
                    for (size_t index = 0; index < max_index; ++index) {
                        auto temp = _resv[index] == baust.Calculate(_sigv[index].slot1, _sigv[index].slot2, _sigv[index].slot3, _sigv[index].slot4);
                        if (!temp) {
                            break;
                        }
                        diff[index] = temp;
                        if (index + 1 >= max_index) {
                            std::get<0>(res) = i1;
                            std::get<1>(res) = i2;
                            std::get<2>(res) = i3;

                            break;
                        }
                    }
                }
            }
        }
        return res;
    }
}

using namespace NetworkSimulation;

int main()
{
    unsigned short max_index{ 16 };

    
    std::vector<Signal> sigv(max_index);
    std::vector<bool> resv(max_index);
    
    //Input table
    {
        unsigned short index{ 0 };
        for (unsigned short i1 = 0; i1 < 2; ++i1) {
            for (unsigned short i2 = 0; i2 < 2; ++i2) {
                for (unsigned short i3 = 0; i3 < 2; ++i3) {
                    for (unsigned short i4 = 0; i4 < 2; ++i4) {
                        sigv[index].slot1 = (i1) ? true : false;
                        sigv[index].slot2 = (i2) ? true : false;
                        sigv[index].slot3 = (i3) ? true : false;
                        sigv[index].slot4 = (i4) ? true : false;
                        index++;
                    }
                }
            }
        }
    }
    
    //Right hand side
    srand(time(NULL)); 
    {
        auto i1 = rand() % 5;
        auto i2 = rand() % 5;
        auto i3 = rand() % 5;
        Network baust(funcList[i1], funcList[i2], funcList[i3]);
        for (unsigned short index = 0; index < max_index; ++index) {
            resv[index] = baust.Calculate(sigv[index].slot1, sigv[index].slot2, sigv[index].slot3, sigv[index].slot4);
        }
    }
    
    //Solution
    auto result1 = std::make_tuple(Solve(sigv, resv));

    //Input table
    sigv[0].slot1 = false;
    sigv[0].slot2 = false;
    sigv[0].slot3 = false;
    sigv[0].slot4 = false;

    sigv[1].slot1 = false;
    sigv[1].slot2 = false;
    sigv[1].slot3 = false;
    sigv[1].slot4 = true;

    sigv[2].slot1 = false;
    sigv[2].slot2 = false;
    sigv[2].slot3 = true;
    sigv[2].slot4 = false;

    sigv[3].slot1 = false;
    sigv[3].slot2 = false;
    sigv[3].slot3 = true;
    sigv[3].slot4 = true;

    sigv[4].slot1 = false;
    sigv[4].slot2 = true;
    sigv[4].slot3 = false;
    sigv[4].slot4 = false;

    sigv[5].slot1 = false;
    sigv[5].slot2 = true;
    sigv[5].slot3 = false;
    sigv[5].slot4 = true;

    sigv[6].slot1 = false;
    sigv[6].slot2 = true;
    sigv[6].slot3 = true;
    sigv[6].slot4 = false;

    sigv[7].slot1 = false;
    sigv[7].slot2 = true;
    sigv[7].slot3 = true;
    sigv[7].slot4 = true;

    sigv[8].slot1 = true;
    sigv[8].slot2 = false;
    sigv[8].slot3 = false;
    sigv[8].slot4 = false;

    sigv[9].slot1 = true;
    sigv[9].slot2 = false;
    sigv[9].slot3 = false;
    sigv[9].slot4 = true;

    sigv[10].slot1 = true;
    sigv[10].slot2 = false;
    sigv[10].slot3 = true;
    sigv[10].slot4 = false;

    sigv[11].slot1 = true;
    sigv[11].slot2 = false;
    sigv[11].slot3 = true;
    sigv[11].slot4 = true;

    sigv[12].slot1 = true;
    sigv[12].slot2 = true;
    sigv[12].slot3 = false;
    sigv[12].slot4 = false;

    sigv[13].slot1 = true;
    sigv[13].slot2 = true;
    sigv[13].slot3 = false;
    sigv[13].slot4 = true;

    sigv[14].slot1 = true;
    sigv[14].slot2 = true;
    sigv[14].slot3 = true;
    sigv[14].slot4 = false;

    sigv[15].slot1 = true;
    sigv[15].slot2 = true;
    sigv[15].slot3 = true;
    sigv[15].slot4 = true;

    //Right hand side
    resv[0] = false;
    resv[1] = false;
    resv[2] = false;
    resv[3] = false;
    resv[4] = false;
    resv[5] = true;
    resv[6] = true;
    resv[7] = false;
    resv[8] = false;
    resv[9] = true;
    resv[10] = true;
    resv[11] = false;
    resv[12] = false;
    resv[13] = false;
    resv[14] = false;
    resv[15] = false;

    auto result2 = std::make_tuple(Solve(sigv, resv));

}

