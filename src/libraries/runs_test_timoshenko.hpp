#pragma once

#include "runs_test.hpp"

namespace runs_test {

    using bytes = std::vector<uint8_t>;

    class Runs_test_timoshenko : public Runs_test
    {
        public:
            Runs_test_timoshenko() = default;
            Runs_test_timoshenko(const Runs_test_timoshenko &runs_test_timoshenko) = default;
            Runs_test_timoshenko(Runs_test_timoshenko &&runs_test_timoshenko) = default;
            Runs_test_timoshenko& operator=(const Runs_test_timoshenko &runs_test_timoshenko) = default;
            Runs_test_timoshenko& operator=(Runs_test_timoshenko &&runs_test_timoshenko) = default;
            ~Runs_test_timoshenko() = default;

            void read(std::string filename = "") override;

            double run_test() const override;

        private:
            std::pair<uint64_t, uint64_t> ones_V_counter() const;

            std::size_t get_size_file(std::string filename) const;

            bytes _buffer;
    };  

} //namespace runs_test