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


long long testFullDynamic(int size) {
    std::string sz = std::to_string(size);
    std::string infile = "tests/tree_tests/tree_" + sz +".txt";
    std::string outfile = "tests/tree_tests/tree_answer_2_" + sz +".txt";
    std::ifstream ifs(infile, std::ifstream::in);
    std::ofstream ofs(outfile, std::ofstream::out);
    int N;
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
    auto t1 = std::chrono::high_resolution_clock::now();
    FullDynamic graph = FullDynamic();
    for(int i = 0; i < N; i++) {
        graph.add(i);
    }
    for(uint i = 0; i < commands.size(); i += 3){
        int c = commands[i];
        int a = commands[i+1];
        int b = commands[i+2];
        if(c == 0)
            graph.link(a, b);
        else if(c == 1)
            graph.cut(a, b);
        else if(c == 2) {
            results.push_back(graph.conn(a, b));
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    long long runtime = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
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
    return runtime;
}

long long testETT(int size) {
    std::string sz = std::to_string(size);
    std::string infile = "tests/tree_tests/tree_" + sz +".txt";
    std::string outfile = "tests/tree_tests/tree_answer_3_" + sz +".txt";
    std::ifstream ifs(infile, std::ifstream::in);
    std::ofstream ofs(outfile, std::ofstream::out);
    int N;
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
    auto t1 = std::chrono::high_resolution_clock::now();
    EulerTourTree graph = EulerTourTree();
    // for(int i = 0; i < N; i++) {
    //     graph.add(i);
    // }
    for(uint i = 0; i < commands.size(); i += 3){
        int c = commands[i];
        int a = commands[i+1];
        int b = commands[i+2];
        if(c == 0)
            graph.link(a, b);
        else if(c == 1)
            graph.cut(a, b);
        else if(c == 2) {
            results.push_back(graph.conn(a, b));
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    long long runtime = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
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
    return runtime;
}

long long testLCT(int size) {
    std::string sz = std::to_string(size);
    std::string infile = "tests/tree_tests/tree_" + sz +".txt";
    std::string outfile = "tests/tree_tests/tree_answer_4_" + sz +".txt";
    std::ifstream ifs(infile, std::ifstream::in);
    std::ofstream ofs(outfile, std::ofstream::out);
    int N;
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
    auto t1 = std::chrono::high_resolution_clock::now();
    LinkCutTree graph = LinkCutTree(N);
    // for(int i = 0; i < N; i++) {
    //     graph.add(i);
    // }
    for(uint i = 0; i < commands.size(); i += 3){
        int c = commands[i];
        int a = commands[i+1] + 1;
        int b = commands[i+2] + 1;
        if(c == 0) {
            // std::cout << "link " << a << ' ' << b;
            graph.link(a, b);
        }
        else if(c == 1) {
            // std::cout << "cut " << a << ' ' << b;
            graph.cut(a, b);
        }
        else if(c == 2) {
            // std::cout << "conn " << a << ' ' << b;
            results.push_back(graph.conn(a, b));
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    long long runtime = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
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
    return runtime;
}

std::pair<double, double> testAll(int size) {
    testUnionFind();
    testSplayTree();
    long long fd = testFullDynamic(size);
    long long ett = testETT(size);
    long long lct = testLCT(size);
    // std::cout << "All tests passed!" << std::endl;
    return std::pair<long long, long long>(fd, ett);
}

int main() {
    std::ofstream timeout("time.txt", std::ofstream::out);
    int tests[] = {100, 1000, 10000, 100000, 1000000, 5000000};
    for(int testSize: tests) {
        std::pair<long long, long long> results = testAll(testSize);
        timeout<< results.first << ',' << results.second << '\n';
    }
    return 0;
}
