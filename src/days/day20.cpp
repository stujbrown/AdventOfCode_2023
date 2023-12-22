#include "aoc_days.hpp"
#include <vector>
#include <sstream>
#include <map>
#include <optional>

namespace
{
    enum class GateType : uint8_t { broadcast, flip_flop, conjunction };
    enum class PulseType : uint8_t { low_pulse, high_pulse };
    struct Gate
    {
        std::string id;
        GateType type;
        std::vector<std::shared_ptr<Gate>> connected;

        bool flipflop_on = false;
        std::map<std::string, PulseType> conjunction_memory;

    };

    struct Pulse
    {
        std::string from_id;
        PulseType type;
        std::shared_ptr<Gate> receiver;
    };
}

void aoc::day20()
{
    std::map<std::string, std::shared_ptr<Gate>> gates;

    std::ifstream file("inputs/day20.txt");
    std::string line;
    while (std::getline(file, line))
    {
        const size_t connector_idx = line.find("->");
        const std::string id = (line[0] == '%' || line[0] == '&') ? line.substr(1, connector_idx - 2) : line.substr(0, connector_idx - 1);

        auto existing_entry = gates.find(id);
        if (existing_entry == gates.end())
        {
            std::shared_ptr<Gate> new_gate(new Gate{ .id = id });
            existing_entry = gates.insert(std::make_pair(new_gate->id, new_gate)).first;
        }

        GateType type = GateType::broadcast;
        if (line[0] == '%')
            type = GateType::flip_flop;
        else if (line[0] == '&')
        {
            type = GateType::conjunction;
        }

        existing_entry->second->type = type;

        std::stringstream ss(line.substr(connector_idx + 3));
        while (std::getline(ss, line, ','))
        {
            line.erase(0, line.find_first_not_of(' '));

            auto existing_connected_entry = gates.find(line);
            if (existing_connected_entry == gates.end())
            {
                std::shared_ptr<Gate> new_gate(new Gate{ .id = line });
                existing_connected_entry = gates.insert(std::make_pair(new_gate->id, new_gate)).first;
            }
            existing_entry->second->connected.push_back(existing_connected_entry->second);
        }
    }

    for (auto& gate : gates)
    {
        for (auto& connection : gate.second->connected)
        {
            const auto existing_memory = connection->conjunction_memory.find(gate.second->id);
            if (existing_memory == connection->conjunction_memory.end())
                connection->conjunction_memory.insert(std::make_pair(gate.second->id, PulseType::low_pulse));
        }
    }

    size_t total_low_pulses = 0, total_high_pulses = 0;

    const Pulse initial_state{ .from_id = "", .type = PulseType::low_pulse, .receiver = gates["broadcaster"] };
    std::vector<Pulse> pulses;

    for (size_t i = 0; i < 1000; ++i)
    {
        pulses.push_back(initial_state);
        while (!pulses.empty())
        {
            std::vector<Pulse> new_pulses_list;
            for (const auto& pulse : pulses)
            {
                if (pulse.type == PulseType::low_pulse)
                    ++total_low_pulses;
                else
                    ++total_high_pulses;

                Gate* this_gate = pulse.receiver.get();
                std::optional<PulseType> value;
                switch (this_gate->type)
                {
                case GateType::flip_flop:
                    if (pulse.type == PulseType::low_pulse)
                    {
                        this_gate->flipflop_on = !this_gate->flipflop_on;
                        value = this_gate->flipflop_on ? PulseType::high_pulse : PulseType::low_pulse;
                    }
                    break;
                case GateType::conjunction:
                {
                    bool all_high = true;
                    this_gate->conjunction_memory[pulse.from_id] = pulse.type;
                    for (const auto& memory : this_gate->conjunction_memory)
                    {
                        if (memory.second == PulseType::low_pulse)
                            all_high = false;
                    }
                    value = all_high ? PulseType::low_pulse : PulseType::high_pulse;

                }
                break;
                default:
                    value = pulse.type;
                    break;
                }

                for (const auto& gate : this_gate->connected)
                {
                    if (value.has_value())
                        new_pulses_list.push_back(Pulse{ .from_id = this_gate->id, .type = *value, .receiver = gate });
                }
            }


            pulses = new_pulses_list;
        }
    }

    std::cout << "Pulse sum: " << total_low_pulses * total_high_pulses << std::endl;
}