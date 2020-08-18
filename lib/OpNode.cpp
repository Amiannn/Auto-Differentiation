#include "OpNode.h"

OpNode::OpNode(std::string tag)
{
    this->Set(0.0);
    this->OpMode = 0;
    this->a = NULL;
    this->b = NULL;
    this->diff = 0;
    this->tag = tag;
    this->freeze = false;
}

int OpNode::GetMode()
{
    return this->OpMode;
}

float OpNode::Get()
{
    return this->value;
}

OpNode* OpNode::Set(float a)
{
    this->value = a;
    this->OpMode = 0;
    return this;
}


OpNode* OpNode::ALU(OpNode* a, OpNode* b, int Mode)
{
    this->OpMode = Mode;
    this->a = a;
    this->b = b;

    switch(this->OpMode)
    {
        // set
        case 0:

        break;

        // add
        case 1:
            this->value = a->value + b->value;
        break;

        // mul
        case 2:
            this->value = a->value * b->value;
        break;

        // pow
        case 3:
            this->value = pow(a->value, b->value);
        break;
    }
    return this;
}

void OpNode::dif()
{
    switch(this->OpMode)
    {
        // set
        case 0:

        break;

        // add
        case 1:
            this->a->diff += this->diff * 1;
            this->b->diff += this->diff * 1;
        break;

        // mul
        case 2:
            this->a->diff += this->diff * this->b->value;
            this->b->diff += this->diff * this->a->value;
        break;

        // pow
        case 3:
            this->a->diff += this->diff * (this->b->value * pow(this->a->value, (this->b->value - 1)));
            this->b->diff += this->diff * (log(this->a->value) * pow(this->a->value, this->b->value));
        break;
    }
}

void OpNode::Show()
{
    char op_str[][4] = {"set", "add", "mul", "pow"};
    
    std::cout << "[Node: " << this->tag << "]\t";
    
    if(this->OpMode)
        std::cout << "Op: " << op_str[this->OpMode] << "(" << this->a->tag << ", " << this->b->tag << "),\t";
    else
        std::cout << "Op: " << op_str[this->OpMode] << "(" << this->tag << "),\t\t";
    
    std::cout << "value: " << this->value << ",\t";

    std::cout << "diff: " << this->diff << std::endl;
}