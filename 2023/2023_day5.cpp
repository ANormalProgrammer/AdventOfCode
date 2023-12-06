#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <limits>

bool compare(const std::vector<long long>& a, const std::vector<long long>& b)
{
    return a[1] <= b[1];
}

std::vector<std::string> processInput()
{
    std::string s;
    std::vector<std::string> input;
    while(std::getline(std::cin, s))
    {
        input.push_back(s);
    }
    return input;
}

bool is_number(std::string str)
{
    for(auto c : str)
    {
        if (c <'0' || c > '9')
        {
            return false;
        }
    }
    return true;
}
std::vector<long long> get_int (std::string line)
{
    std::vector<long long> int_list;
    std::stringstream ss (line);
    std::string token;
    while(ss >> token)
    {
        if(!token.empty() && is_number(token))
        {
            int_list.push_back(std::stoll(token));
        }
    }
    return int_list;
}

std::vector<std::vector<long long>> get_source_to_destination_map(const std::vector<std::string>& input, std::string type_of_map)
{
    std::vector<std::vector<long long>> source_to_destination;

    auto position = std::distance(input.begin(), std::find(input.begin(), input.end(), type_of_map));

    std::vector<long long> list_of_maps (0, 3);
    do
    {
        ++position;
        if(position == input.size()) break;

        list_of_maps = get_int(input[position]);

        if(list_of_maps.size() != 3) break;


        source_to_destination.push_back(list_of_maps);

    }
    while(true);

    std::sort(source_to_destination.begin(), source_to_destination.end(), compare);

    return source_to_destination;
}
void source_to_destination_seed(std::vector<std::vector<long long>>& seeds,
                                std::vector<std::vector<long long>> map_type,
                                std::vector<std::vector<long long>>& destination_pair_after_change)
{
    std::vector<long long> seed = seeds[0];

    long long destination_pair_start = 0;

    long long destination_pair_range = 0;
    long long destination_pair_end = 0;

    long long seed_value_start = seed[0];
    long long seed_range_length = seed[1];
    long long seed_value_end = seed_value_start + seed_range_length - 1;
    for(auto map_num : map_type)
    {
        long long destination_range_start = map_num[0];
        long long source_range_start = map_num[1];
        long long range_length  = map_num[2];
        long long source_range_end = source_range_start + range_length - 1;

        if(seed_value_end >= source_range_start && source_range_end >= seed_value_start)
        {
            if(seed_value_end <= source_range_end)
            {
                if(seed_value_start < source_range_start)
                {
                    destination_pair_start = destination_range_start;
                    destination_pair_range = seed_value_end - source_range_start + 1;

                    destination_pair_after_change.push_back({destination_pair_start, destination_pair_range});

                    long long new_seed_start = seed_value_start;
                    long long new_seed_end = source_range_start - 1;
                    long long new_seed_range = new_seed_end - new_seed_start + 1;

                    seeds.push_back({new_seed_start, new_seed_range});
                    seeds.erase (seeds.begin());

                    return;
                }
                else if(seed_value_start >= source_range_start)
                {
                    destination_pair_start = seed_value_start + destination_range_start - source_range_start;
                    destination_pair_range = seed_range_length;

                    destination_pair_after_change.push_back({destination_pair_start, destination_pair_range});
                    seeds.erase (seeds.begin());

                    return;
                }
            }
            else if(seed_value_end > source_range_end)
            {
                if(seed_value_start < source_range_start)
                {
                    destination_pair_start = destination_range_start;
                    destination_pair_range = range_length;

                    destination_pair_after_change.push_back({destination_pair_start, destination_pair_range});

                    long long new_seed_start_1 = seed_value_start;
                    long long new_seed_end_1 = source_range_start - 1;
                    long long new_seed_range_1 = new_seed_end_1 - new_seed_start_1 + 1;

                    seeds.push_back({new_seed_start_1, new_seed_range_1});

                    long long new_seed_start_2 = source_range_end + 1;
                    long long new_seed_end_2 = seed_value_end;
                    long long new_seed_range_2 = new_seed_end_2 - new_seed_start_2 + 1;

                    seeds.push_back({new_seed_start_1, new_seed_range_2});
                    seeds.erase (seeds.begin());

                    return;
                }
                else if(seed_value_start >= source_range_start)
                {
                    destination_pair_start = seed_value_start + destination_range_start - source_range_start;;
                    destination_pair_range = source_range_end - seed_value_start + 1;

                    destination_pair_after_change.push_back({destination_pair_start, destination_pair_range});

                    long long new_seed_start = source_range_end + 1;
                    long long new_seed_end = seed_value_end;
                    long long new_seed_range = new_seed_end - new_seed_start + 1;

                    seeds.push_back({new_seed_start, new_seed_range});
                    seeds.erase(seeds.begin());

                    return;
                }
            }
        }
    }
    destination_pair_start = seed_value_start;
    destination_pair_range = seed_range_length;
    destination_pair_after_change.push_back({destination_pair_start, destination_pair_range});

    seeds.erase (seeds.begin());
}
namespace part_1
{
    long long source_to_destination (long long source, std::vector<std::vector<long long>> map_type)
    {
        for(const auto&  list_of_map : map_type)
        {
            long long destination_range_start = list_of_map[0];
            long long source_range_start = list_of_map[1];
            long long range_length  = list_of_map[2];

            if(source >= source_range_start && source <= source_range_start + range_length - 1)
                return source + destination_range_start - source_range_start;
        }
        return source;
    }
}
namespace part_2
{
    std::vector<std::vector<long long>> source_to_destination (std::vector<std::vector<long long>>& seeds, std::vector<std::vector<long long>> map_type)
    {
        std::vector<std::vector<long long>> destination_pair_after_change;
        while(!seeds.empty())
        {
            source_to_destination_seed(seeds, map_type, destination_pair_after_change);
        }
        return destination_pair_after_change;
    }
}
long long part1(const std::vector<std::string>& input)
{

    std::vector<long long> seeds = get_int(input[0]);

    std::vector<std::vector<long long>> seed_to_soil_map            = get_source_to_destination_map(input, "seed-to-soil map:");
    std::vector<std::vector<long long>> soil_to_fertilizer_map      = get_source_to_destination_map(input, "soil-to-fertilizer map:");
    std::vector<std::vector<long long>> fertilizer_to_water_map     = get_source_to_destination_map(input, "fertilizer-to-water map:");
    std::vector<std::vector<long long>> water_to_light_map          = get_source_to_destination_map(input, "water-to-light map:");
    std::vector<std::vector<long long>> light_to_temperature_map    = get_source_to_destination_map(input, "light-to-temperature map:");
    std::vector<std::vector<long long>> temperature_to_humidity_map = get_source_to_destination_map(input, "temperature-to-humidity map:");
    std::vector<std::vector<long long>> humidity_to_location_map    = get_source_to_destination_map(input, "humidity-to-location map:");

    long long lowest_location_number = std::numeric_limits<long long>::max();

    for(auto seed : seeds)
    {
        long long soil        = part_1::source_to_destination(seed, seed_to_soil_map);
        long long fertilizer  = part_1::source_to_destination(soil, soil_to_fertilizer_map);
        long long water       = part_1::source_to_destination(fertilizer, fertilizer_to_water_map);
        long long light       = part_1::source_to_destination(water, water_to_light_map);
        long long temperature = part_1::source_to_destination(light, light_to_temperature_map);
        long long humidity    = part_1::source_to_destination(temperature, temperature_to_humidity_map);
        long long location    = part_1::source_to_destination(humidity, humidity_to_location_map);


        lowest_location_number = std::min(lowest_location_number, location);

    }

    return lowest_location_number;
}
long long part2(const std::vector<std::string>& input)
{

    std::vector<long long> seeds_input = get_int(input[0]);
    std::vector<std::vector<long long>> seeds;

    for(int i = 0; i < seeds_input.size(); i += 2)
    {
        std::vector<long long> seed_pair;
        seed_pair.push_back(seeds_input[i]);
        seed_pair.push_back(seeds_input[i + 1]);
        seeds.push_back(seed_pair);
    }


    std::vector<std::vector<long long>> seed_to_soil_map            = get_source_to_destination_map(input, "seed-to-soil map:");
    std::vector<std::vector<long long>> soil_to_fertilizer_map      = get_source_to_destination_map(input, "soil-to-fertilizer map:");
    std::vector<std::vector<long long>> fertilizer_to_water_map     = get_source_to_destination_map(input, "fertilizer-to-water map:");
    std::vector<std::vector<long long>> water_to_light_map          = get_source_to_destination_map(input, "water-to-light map:");
    std::vector<std::vector<long long>> light_to_temperature_map    = get_source_to_destination_map(input, "light-to-temperature map:");
    std::vector<std::vector<long long>> temperature_to_humidity_map = get_source_to_destination_map(input, "temperature-to-humidity map:");
    std::vector<std::vector<long long>> humidity_to_location_map    = get_source_to_destination_map(input, "humidity-to-location map:");

    std::vector<std::vector<long long>> soil        = part_2::source_to_destination(seeds, seed_to_soil_map);
    std::vector<std::vector<long long>> fertilizer  = part_2::source_to_destination(soil, soil_to_fertilizer_map);
    std::vector<std::vector<long long>> water       = part_2::source_to_destination(fertilizer, fertilizer_to_water_map);
    std::vector<std::vector<long long>> light       = part_2::source_to_destination(water, water_to_light_map);
    std::vector<std::vector<long long>> temperature = part_2::source_to_destination(light, light_to_temperature_map);
    std::vector<std::vector<long long>> humidity    = part_2::source_to_destination(temperature, temperature_to_humidity_map);
    std::vector<std::vector<long long>> location    = part_2::source_to_destination(humidity, humidity_to_location_map);

    long long lowest_location_number = std::numeric_limits<long long>::max();

    for(auto loc : location)
    {
        lowest_location_number = std::min(loc[0], lowest_location_number);
    }

    return lowest_location_number;
}
int main()
{
    //std::freopen("day5inp.txt", "r", stdin);
    //std::freopen("day5out.txt", "w", stdout);

    std::vector<std::string> input = processInput();

    std::cout << "The solution for part 1 is: " << part1(input) <<'\n';
    std::cout << "The solution for part 2 is: " << part2(input) <<'\n';
}
