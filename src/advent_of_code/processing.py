""""""
from typing import List
from pathlib import Path

import advent_processing
from advent_processing import Day, Day1

def available_days():
    """
    Let's do some ugly hacks just once
    """

    namespace_entries = dir(advent_processing)

    # get all Day implementations
    days = [entry for entry in namespace_entries if entry.startswith('Day')]

    # filter base class Day
    days = [day for day in days if len(day) > 3]

    return days

def run_day(day_name: str, input_file_path: str):
    """
    Dynamically import the argument classes
    """
    try:
        DayClass = getattr(advent_processing, day_name)
    except AttributeError:
        raise RuntimeError("Trying to load an unavailable day: {}".format(day_name))

    # get the input file 
    input_file = Path(input_file_path)
    if not input_file.exists():
        raise OSError(f"No required input: {input_file} for processing day: {day_name}")

    day: Day = DayClass()

    print(f"Processing day: {day_name}")
    day.process(str(input_file))

def run_all(days: List[str]):
    """Just a simple helper
    
    Try to load the input files from 'inputs' directory
    """

    input_dir =  Path(__file__).parent.parent.parent / 'inputs'

    for day in days:
        input_file = input_dir / (day.lower() + '.txt')
        run_day(day, str(input_file))


def main():
    """An entry point"""

    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--run', required=True, help="Which day to run, specify either 'all' or 'day<day-number>'")
    parser.add_argument('--input', help="Path to the input file to use for a single day.'")

    args = parser.parse_args()

    all_days = available_days()
    if args.run == 'all':
        run_all(all_days)
        return

    if args.run not in all_days:
        raise RuntimeError("You tried to run an unavailable day {}, available days are: {}".format(args.run, all_days))

    if not args.input:
        print("Give the input file as argument when processing single day")
        return
    run_day(args.run, args.input)


if __name__ == "__main__":
    main()
        

    