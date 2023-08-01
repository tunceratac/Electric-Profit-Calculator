# Electric Profit Calculation Program
This C program is used to calculate how much electric profit a charging station installed on a road will make over the course of a year. The program takes input from the user, such as road length, CPT (Charging Power Technology) power, and the percentage of road covered by CPT, to calculate daily electric profit and show the total electric profit for the entire year.

# Inputting Road and CPT Data
The program prompts the user to enter the following data:

- Road length (in kilometers)
- CPT power (should be between 10 kW and 50 kW)
- Percentage of road covered by CPT (should be between 10% and 100%)
If the user enters values outside the specified range, the program requests the input to be repeated.

# Assigning Random Daily Car Count
The program generates a random car count for each day. Higher car counts are assigned for June, July, and August (from day 152 to day 244), and lower car counts for other days.

# Reading Daily KW Costs from CSV
The program reads daily KW costs from a CSV file named prices.csv. This file should contain one daily KW cost per line.

# Calculating Electric Profit
Based on the road and CPT data input by the user, the program calculates the electric profit for each day. The electric profit is calculated using the daily KW cost, daily car count, and road data.

# Displaying Results and Writing to File
The program calculates the total car count, total KW energy production, and total electric profit for the year and displays them on the screen. It also writes the calculated daily data to a text file named dailyData.txt.

# How to Use?
Compile the code in main.c using a C compiler.
Run the resulting executable.
The program will prompt you to enter road and CPT data.
You will see the total car count, total KW energy production, and total electric profit for the entire year.
Additionally, the dailyData.txt file will contain the calculated daily data.


# Sample Output
```
Enter the road length in km: 100
Enter the CPT power (between 10-50 kW): 30
Enter the CPT's percentage on the road (between 10-100%): 20
Calculated KW Energy: 3600.00
Total Car Count for the year: 23259890 Cars
Total KW Profit for the year: 83975496000.00 Kw
Total Electric Profit for the year: 1,057,661,441.53 TL
```

# Note
- For the program to work correctly, the prices.csv file must contain valid and accurate data.
- The total car count and electric profit collected over the year may vary with each run due to the randomly generated daily car counts.
