import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()
    previous_cases = dict()

    for row in reader:
        state = row.get("state")
        previous = previous_cases.get(state, 0)

        old_cases = new_cases.get(state, [])
        if (len(old_cases) > 13):
            _ = old_cases.pop(0)

        new = int(row["cases"]) - previous
        new_cases.update({state: old_cases + [new]})
        previous_cases[state] = int(row["cases"])

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        state_cases = new_cases[state]
        first_week_avg = sum(state_cases[:7]) / 7.0
        second_week_avg = sum(state_cases[7:]) / 7.0

        diff = second_week_avg - first_week_avg
        try:
            change = diff / first_week_avg
        except ZeroDivisionError:
            print("Dunno")
        else:
            print(f"{state} had a 7-day average of {int(second_week_avg)} and {'an' if change > 0 else 'a'} {'increase' if change > 0 else 'decrease'} of {change * 100:.1}%.")



main()
