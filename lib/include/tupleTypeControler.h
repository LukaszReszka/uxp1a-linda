#pragma once
#include <map>
#include <deque>
#include <vector>
#include "mutex"
#include "lindaTuple.h"
#include "lindaClient.h"
#include "tupleCondition.h"

class TupleTypeControler{
    public:
        TupleTypeControler();
        bool checkOperations();
        void addToQue();
        void lockOnQue();
        void unlockQue();
        void lockTuples();
        void unlockTuples();
        uxp::Tuple readTuple(const TupleCondition & tupleCond);
        uxp::Tuple getTuple(const TupleCondition& tupleCond);
        void addTuple();
    private:
        std::vector<uxp::Tuple> tuples;
        uxp::mutex tupleMtx;
        std::deque<LindaClient> clients;
        uxp::mutex clientMtx;
};