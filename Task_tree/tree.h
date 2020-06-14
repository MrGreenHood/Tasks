#ifndef TREE_H
#define TREE_H
#include <ctype.h>
#include <stdexcept>
#include <memory>
#include <math.h>
#include <assert.h>
using namespace std;

enum class Operation
{
    NOP, // just a value
    ADD, // +
    SUB, // -
    MUL, // *
    DIV, // /
    MOD, // %
};



class Tree
{
  private:
    struct Expression
    {
        double value = 0;
        Operation op = Operation::NOP;
        Expression *pLeft = nullptr;
        Expression *pRight = nullptr;
    };

    Expression* root;

    double CalculateExpression(Expression *pExpr)
    {
        if (pExpr->op == Operation::NOP)
        {
            return pExpr->value;
        }
        assert(pExpr->pLeft);
        assert(pExpr->pRight);
        CalculateExpression(pExpr->pLeft);
        CalculateExpression(pExpr->pRight);

        switch (pExpr->op)
        {
        case Operation::ADD:
            pExpr->value = pExpr->pLeft->value + pExpr->pRight->value;
            break;
        case Operation::SUB:
            pExpr->value = pExpr->pLeft->value - pExpr->pRight->value;
            break;
        case Operation::MUL:
            pExpr->value = pExpr->pLeft->value * pExpr->pRight->value;
            break;
        case Operation::DIV:
            pExpr->value = pExpr->pLeft->value / pExpr->pRight->value;
            break;
        case Operation::MOD:
            pExpr->value = fmod(pExpr->pLeft->value, pExpr->pRight->value);
            break;
        case Operation::NOP:
            assert(false);
            break;
        }

        return pExpr->value;
    }

public:

    Tree(const string& expression)
    {
        string remaining_str = expression;
        this->root = parse_add_sub(remaining_str);

        skip_spaces(remaining_str);
        if (!remaining_str.empty())
        {
            const auto message = "Unexpected symbol at: " + remaining_str;
            throw std::runtime_error(message);
        }
    }









    void skip_spaces(string &expression)
    {
        unsigned int numSize = 0;
        while (numSize < expression.size()
               && (expression[numSize] == ' '))
        {
            ++numSize;
        }
        expression = expression.substr(numSize);
    }

    bool parse_double(string &expression, double &result)
    {
        string remainingStr = expression;
        skip_spaces(remainingStr);

        unsigned int numSize = 0;
        if (remainingStr.size() > 0 && isdigit(remainingStr[0]))
        {
            while (numSize < remainingStr.size()
                   && isdigit(remainingStr[numSize]))
            {
                ++numSize;
            }
            result = stod(remainingStr.substr(0, numSize));
            expression = remainingStr.substr(numSize);
            return true;
        }

        return false;
    }

    bool parse_operator(string &expression, Operation &op)
    {
        string remaining_str = expression;
        skip_spaces(remaining_str);
        if (remaining_str.empty())
        {
            op = Operation::NOP;
            return false;
        }

        switch (remaining_str[0])
        {
        case '+':
            op = Operation::ADD; break;
        case '-':
            op = Operation::SUB; break;
        case '*':
            op = Operation::MUL; break;
        case '/':
            op = Operation::DIV; break;
        case '%':
            op = Operation::MOD; break;
        default:
            op = Operation::NOP; break;
        }

        const bool succeed = (op != Operation::NOP);
        if (succeed)
        {
            expression = remaining_str.substr(1);
        }
        return succeed;
    }

    Expression * parse_atom(string &str)
    {
        Expression *expr = new Expression;
        skip_spaces(str);
        if(str[0]=='(')
        {
            int index_c=str.rfind(')');
            string subs= str.substr(1,index_c-1);
            expr=parse_add_sub(subs);
            str.erase(0,index_c+1);
        }
        else if (!parse_double(str, expr->value))
        {
            throw std::invalid_argument("Expected number at: " + str);
        }
        return expr;
    }

    Expression* parse_mul_div(string& str)
    {
        Expression* left = parse_atom(str);
        while(true)
        {
            Operation op=Operation::NOP;
            string remaining_str=str;

            if(!parse_operator(remaining_str,op))
            {
                return left;
            }
            switch (op)
            {
            case Operation::MUL:
            case Operation::DIV:
            case Operation::MOD:
                break;
            default:
                return left;
            }
            str=remaining_str;

            Expression* right = parse_atom(str);
            Expression *expr = new Expression;
            expr->pLeft = left;
            expr->pRight = right;
            expr->op = op;
            left = expr;

        }
        return left;
    }

    Expression* parse_add_sub(string &str)
    {
        Expression *left = parse_mul_div(str);
        while (true)
        {
            Operation op = Operation::NOP;
            string remaining_str = str;

            if (!parse_operator(remaining_str, op))
            {
                return left;
            }
            switch (op)
            {
            case Operation::ADD:
            case Operation::SUB:
                break;
            default:
                return left;
            }
            str = remaining_str;

            Expression *right = parse_mul_div(str);

            Expression *expr = new Expression;
            expr->pLeft = left;
            expr->pRight = right;
            expr->op = op;
            left = expr;
        }

        return left;
    }

    double calculate()
    {
        double res= this->CalculateExpression(this->root);
        return res;
    }

    double calculate(const string& expression)
    {
        string remaining_str = expression;
        this->root = parse_add_sub(remaining_str);

        skip_spaces(remaining_str);
        if (!remaining_str.empty())
        {
            const auto message = "Unexpected symbol at: " + remaining_str;
            throw std::runtime_error(message);
        }
        double res= this->CalculateExpression(this->root);
        return res;
    }

};



#endif // TREE_H
