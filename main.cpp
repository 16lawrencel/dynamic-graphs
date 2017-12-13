#include "ds.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

typedef unsigned int uint;
//simple test for union find

void testUnionFind() {
    UnionFind graph = UnionFind();
    graph.add(1);
    graph.add(2);

    assert(!graph.conn(1, 2));
    graph.merge(1, 2);
    assert(graph.conn(1, 2));
}

void testSplayTree() {
    SplayTree* tree = new SplayTree();
    //todo
}


std::pair<double, double> testFullDynamic(int size) {
    std::string sz = std::to_string(size);
    std::string infile = "tests/tree_tests/tree_" + sz +".txt";
    std::string outfile = "tests/tree_tests/tree_answer_2_" + sz +".txt";
    std::ifstream ifs(infile, std::ifstream::in);
    std::ofstream ofs(outfile, std::ofstream::out);
    int N;
    long long queryTime, updateTime, queryNum, updateNum;
    updateTime = updateNum = queryTime = queryNum = 0;
    bool flag = false;
    ifs >> N;
    std::string cmd;
    std::vector<int> commands;
    std::vector<bool> results;
    int a, b;
    while(ifs >> cmd >> a >> b) {
        if(cmd == "add") {
            commands.push_back(0);
            commands.push_back(a);
            commands.push_back(b);
        } else if(cmd == "rem") {
            commands.push_back(1);
            commands.push_back(a);
            commands.push_back(b);
        } else if(cmd == "conn") {
            commands.push_back(2);
            commands.push_back(a);
            commands.push_back(b);

        }
    }
    auto T1 = std::chrono::high_resolution_clock::now();
    FullDynamic graph = FullDynamic();
    for(int i = 0; i < N; i++) {
        graph.add(i);
    }
    for(uint i = 0; i < commands.size(); i += 3){
        int c = commands[i];
        int a = commands[i+1];
        int b = commands[i+2];
        if(c == 0) {
            auto t1 = std::chrono::high_resolution_clock::now();
            graph.link(a, b);
            auto t2 = std::chrono::high_resolution_clock::now();
            if(flag) {
                updateTime += std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
                updateNum ++;
            }
        }
        else if(c == 1) {
            flag = true;
            auto t1 = std::chrono::high_resolution_clock::now();
            graph.cut(a, b);
            auto t2 = std::chrono::high_resolution_clock::now();
            updateTime += std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
            updateNum ++;
        }
        else if(c == 2) {
            flag = true;
            auto t1 = std::chrono::high_resolution_clock::now();
            bool connected = graph.conn(a, b)
            auto t2 = std::chrono::high_resolution_clock::now();
            results.push_back(connected);
            queryTime += std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
            queryNum ++;
        }
    }
    auto T2 = std::chrono::high_resolution_clock::now();
    long long runtime = std::chrono::duration_cast<std::chrono::milliseconds>(T2-T1).count();
    std::cout << "FullDynamic took "
              << runtime
              << " milliseconds\n";

    for(auto res: results) {
        if(res) {
            ofs << "YES\n";
        } else {
            ofs << "NO\n";
        }
    }
    return std::pair<double, double> (updateTime / (updateNum * 1.0), queryTime / (queryNum * 1.0));
}

std::pair<double, double> testETT(int size) {
    std::string sz = std::to_string(size);
    std::string infile = "tests/tree_tests/tree_" + sz +".txt";
    std::string outfile = "tests/tree_tests/tree_answer_3_" + sz +".txt";
    std::ifstream ifs(infile, std::ifstream::in);
    std::ofstream ofs(outfile, std::ofstream::out);
    int N;
    long long updateTime, updateNum, queryTime, queryNum;
    bool flag = false;
    updateTime = updateNum = queryTime = queryNum = 0;
    ifs >> N;
    std::string cmd;
    std::vector<int> commands;
    std::vector<bool> results;
    int a, b;
    while(ifs >> cmd >> a >> b) {
        if(cmd == "add") {
            commands.push_back(0);
            commands.push_back(a);
            commands.push_back(b);
        } else if(cmd == "rem") {
            commands.push_back(1);
            commands.push_back(a);
            commands.push_back(b);
        } else if(cmd == "conn") {
            commands.push_back(2);
            commands.push_back(a);
            commands.push_back(b);

        }
    }
    auto T1 = std::chrono::high_resolution_clock::now();
    EulerTourTree graph = EulerTourTree();
    for(uint i = 0; i < commands.size(); i += 3){
        int c = commands[i];
        int a = commands[i+1];
        int b = commands[i+2];
        if(c == 0) {
            auto t1 = std::chrono::high_resolution_clock::now();
            graph.link(a, b);
            auto t2 = std::chrono::high_resolution_clock::now();
            if(flag) {
                updateTime += std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
                updateNum ++;
            }
        }
        else if(c == 1) {
            flag = true;
            auto t1 = std::chrono::high_resolution_clock::now();
            graph.cut(a, b);
            auto t2 = std::chrono::high_resolution_clock::now();
            updateTime += std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
            updateNum ++;
        }
        else if(c == 2) {
            flag = true;
            auto t1 = std::chrono::high_resolution_clock::now();
            bool connected = graph.conn(a, b)
            auto t2 = std::chrono::high_resolution_clock::now();
            results.push_back(connected);
            queryTime += std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
            queryNum ++;
        }
    }
    auto T2 = std::chrono::high_resolution_clock::now();
    long long runtime = std::chrono::duration_cast<std::chrono::milliseconds>(T2-T1).count();
    std::cout << "ETT took "
              << runtime
              << " milliseconds\n";

    for(auto res: results) {
        if(res) {
            ofs << "YES\n";
        } else {
            ofs << "NO\n";
        }
    }
    return std::pair<double, double> (updateTime / (updateNum * 1.0), queryTime / (queryNum * 1.0));
}

std::pair<double, double> testLCT(int size) {
    std::string sz = std::to_string(size);
    std::string infile = "tests/tree_tests/tree_" + sz +".txt";
    std::string outfile = "tests/tree_tests/tree_answer_4_" + sz +".txt";
    std::ifstream ifs(infile, std::ifstream::in);
    std::ofstream ofs(outfile, std::ofstream::out);
    int N;
    long long updateTime, updateNum, queryTime, queryNum;
    bool flag = false;
    updateTime = updateNum = queryTime = queryNum = 0;
    ifs >> N;
    std::string cmd;
    std::vector<int> commands;
    std::vector<bool> results;
    int a, b;
    while(ifs >> cmd >> a >> b) {
        if(cmd == "add") {
            commands.push_back(0);
            commands.push_back(a);
            commands.push_back(b);
        } else if(cmd == "rem") {
            commands.push_back(1);
            commands.push_back(a);
            commands.push_back(b);
        } else if(cmd == "conn") {
            commands.push_back(2);
            commands.push_back(a);
            commands.push_back(b);

        }
    }
    auto T1 = std::chrono::high_resolution_clock::now();
    LinkCutTree graph = LinkCutTree(N);
    // for(int i = 0; i < N; i++) {
    //     graph.add(i);
    // }
    for(uint i = 0; i < commands.size(); i += 3){
        int c = commands[i];
        // add one because 0 isn't a valid node here
        int a = commands[i+1] + 1;
        int b = commands[i+2] + 1;
        if(c == 0) {
            auto t1 = std::chrono::high_resolution_clock::now();
            graph.link(a, b);
            auto t2 = std::chrono::high_resolution_clock::now();
            if(flag) {
                updateTime += std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
                updateNum ++;
            }
        }
        else if(c == 1) {
            flag = true;
            auto t1 = std::chrono::high_resolution_clock::now();
            graph.cut(a, b);
            auto t2 = std::chrono::high_resolution_clock::now();
            updateTime += std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
            updateNum ++;
        }
        else if(c == 2) {
            flag = true;
            auto t1 = std::chrono::high_resolution_clock::now();
            bool connected = graph.conn(a, b)
            auto t2 = std::chrono::high_resolution_clock::now();
            results.push_back(connected);
            queryTime += std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
            queryNum ++;
        }
    }
    auto T2 = std::chrono::high_resolution_clock::now();
    long long runtime = std::chrono::duration_cast<std::chrono::milliseconds>(T2-T1).count();
    std::cout << "LCT took "
              << runtime
              << " milliseconds\n";

    for(auto res: results) {
        if(res) {
            ofs << "YES\n";
        } else {
            ofs << "NO\n";
        }
    }
    return std::pair<double, double> (updateTime / (updateNum * 1.0), queryTime / (queryNum * 1.0));;
}

std::vector<pair<double, double> > testAll(int size) {
    testUnionFind();
    testSplayTree();
    std::pair<double, double> fd = testFullDynamic(size);
    std::pair<double, double> ett = testETT(size);
    std::pair<double, double> lct = testLCT(size);
    // std::cout << "All tests passed!" << std::endl;
    return std::vector<pair<long long, long long> >({fd, ett, lct});
}

int main() {
    std::ofstream timeout("time_all.txt", std::ofstream::out);
    int tests[] = {100, 1000, 10000, 100000, 1000000, 5000000};
    for(int testSize: tests) {
        std::pair<long long, long long> results = testAll(testSize);
        for(pair<double, double> result: results)
            timeout<< result.first << ',' << result.second << ',';
        timeout << testSize << '\n';
    }
    return 0;
}
