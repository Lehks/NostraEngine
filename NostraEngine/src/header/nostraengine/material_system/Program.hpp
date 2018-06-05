#ifndef NOE_MATSYS_PROGRAM_HPP
#define NOE_MATSYS_PROGRAM_HPP

#include "nostrautils/NostraUtils.hpp"
#include "nostraengine/NostraEngine.hpp"

namespace NOE::NOE_MATSYS
{
    class NOU_CLASS Program
    {
    public:
        enum class Variables
        {
            INT,
            FLOAT,
            BOOLEAN,
            VEC1,
            VEC2,
            VEC3,
            VEC4,
            MAT1,
            MAT2,
            MAT3,
            MAT4
        };

    public:
        virtual ~Program() = default;

        virtual NOU::boolean createShader() = 0;

        virtual NOU::boolean bind() = 0;
    };
}
#endif