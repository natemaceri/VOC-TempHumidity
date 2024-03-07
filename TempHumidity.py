# Program for temperature and humidity processing
# BLiSS-VOC
# Nate Maceri

def main():
    # get choice of temperature or humidity
    print("Temperature or humidity?")
    print("1. Temperature")
    print("2. Humidity")
    choice = int(input("Choice: "))
    if choice == 1:
        temp = True
    elif choice == 2:
        temp = False
    else:
        print("Enter 1 for temperature or 2 for humidity")
        exit(1)
    print()

    # get data filename
    filename = input("Enter data filename: ")
    filename += ".txt"

    # open temperature and humidity data files
    try:
        with open(filename, 'r') as data:
            # determine nominal value
            dataCount = 0
            currValue = 0
            nominal = 0
            for line in data:
                line = line.strip()  # remove leading/trailing whitespace
                if not line:
                    continue  # skip empty lines
                parts = line.split(',')
                date_time, currValue = parts[0], float(parts[1])
                nominal += currValue
                dataCount += 1
            if dataCount == 0:
                print("No valid data found in the file.")
                exit(1)
            nominal = round(nominal / dataCount, 3)
            print("\nNominal:", nominal, "\n")

            # set upper and lower bounds on nominal value
            upper = nominal + 2
            lower = nominal - 2

            # reset file input buffer
            data.seek(0)

            # determine if any data points exceed +-2 of nominal
            exceeded = False
            difference = 0
            for line in data:
                line = line.strip()  # remove leading/trailing whitespace
                if not line:
                    continue  # skip empty lines
                parts = line.split(',')
                date_time, currValue = parts[0], float(parts[1])
                date, time, AM_PM = date_time.split()
                if currValue > upper or currValue < lower:
                    difference = round(currValue - nominal, 3)
                    if temp:
                        print("Temperature ", end="")
                    else:
                        print("Humidity ", end="")
                    print("exceeded nominal value of", nominal, "by", difference, "at", date, time, AM_PM)
                    exceeded = True
            if not exceeded:
                if temp:
                    print("Temperature ", end="")
                else:
                    print("Humidity ", end="")
                print("did not exceed nominal value of", nominal)
    except FileNotFoundError:
        print("Data file failed to open")

        # TODO: use numpy and pylot to visualize data

if __name__ == "__main__":
    main()