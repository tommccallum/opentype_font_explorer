#ifndef ABSTRACT_TABLE_H
#define ABSTRACT_TABLE_H

#include <iostream>

namespace OpenType {
    // abstract class that all Tables inherit from
    // requires a virtual destructor
    class AbstractTable {
        virtual void print(std::ostream& out) const = 0;

        friend std::ostream& operator<<( std::ostream& out, AbstractTable const & table );
        friend std::ostream& operator<<( std::ostream& out, AbstractTable const * table );
    public:
        virtual ~AbstractTable() = 0;
    };
}

#endif // ABSTRACT_TABLE_H
