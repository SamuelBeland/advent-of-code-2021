#include <iostream>

#include <resources.hpp>

//==============================================================================
// TODO : add some cleaner CLI options.
int main(int /*argc*/, char const ** /*argv*/)
{
    for (auto const & day : DAYS) {
        std::cout << day.name << ":\n\t" << day.function() << "\n\n";
    }

    return 0;
}