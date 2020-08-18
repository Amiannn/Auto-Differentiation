#ifndef OPNODE_H
#define OPNODE_H
#include <iostream>
#include <string>
#include <math.h>

class OpNode
{
    private:
        float value;
        int OpMode;

    public:
        OpNode* a;
        OpNode* b;
        float diff;
        bool freeze;
        std::string tag;
        OpNode(std::string tag);
        int GetMode();
        float Get();
        void Show();
        OpNode* Set(float a);
        OpNode* ALU(OpNode* a, OpNode* b, int Mode);
        void dif();
};

#endif