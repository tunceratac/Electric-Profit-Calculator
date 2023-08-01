#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    double kw_cost;             // KW cost obtained from the CSV file
    int daily_car_count;        // Daily car count
    double daily_electric_profit; // Daily electric profit calculated using the formula: daily_kw_cost * daily_car_count * kw_energy_value
} DailyData;

typedef struct {
    double road_length;          // Road length
    double cpt_power;            // CPT power
    double cpt_percentage;       // CPT's percentage on the road
    double kw_energy;            // KW energy calculated based on user input
} RoadData;

// Get road data from the user
// If the values are not within the specified range, ask the user to enter a value within that range.
// For example, it will keep asking for a CPT power value until the user enters a value between 10 and 50.
RoadData getRoadData() {
    RoadData data;
    double a;
    printf("Enter the road length in km: ");
    scanf("%lf", &data.road_length);

    do {
        printf("Enter the CPT power (between 10-50 kW): ");
        scanf("%lf", &data.cpt_power);
    } while(data.cpt_power < 10 || data.cpt_power > 50);

    do {
        printf("Enter the CPT's percentage on the road (between 10-100%%): ");
        scanf("%lf", &data.cpt_percentage);
    } while(data.cpt_percentage < 10 || data.cpt_percentage > 100);

    data.kw_energy = (pow(data.road_length, 2) * (data.cpt_percentage * 0.17 * data.cpt_power)) / 10;
    return data;
}

// Assign random car count for each day. 
// The car count is higher from day 152 to day 244 (inclusive) for June, July, and August, and lower for other days.
void assignRandomCarCount(DailyData dailydata[365]) {
    srand(time(NULL)); 
    for(int i = 0; i < 365; i++) {
        if(i >= 152 && i <= 244) { 
            dailydata[i].daily_car_count = 80000 + rand() % (150001 - 80000);
        } else {
            dailydata[i].daily_car_count = 50000 + rand() % (100001 - 50000);
        }
    }
}

// Read daily KW costs from the CSV file and store them in the dailydata array.
void readPricesFromCSV(DailyData dailydata[365]) {
    FILE *file = fopen("prices.csv", "r");
    if(file == NULL) {
        printf("Unable to open prices.csv\n");
        return;
    }

    for(int i = 0; i < 365; i++) {
        fscanf(file, "%lf\n", &dailydata[i].kw_cost);
    }

    fclose(file);
}

// Calculate the daily electric profit for each day.
// The formula is: daily_kw_cost (from CSV) * daily_car_count * kw_energy_value (calculated based on user input)
void calculateDailyElectricProfit(DailyData dailydata[365], RoadData roadData) {
    for(int i = 0; i < 365; i++) {
        dailydata[i].daily_electric_profit = dailydata[i].kw_cost * dailydata[i].daily_car_count * roadData.kw_energy;
    }
}

// Calculate the total car count for the year.
int printTotalCarCount(DailyData dailydata[365]) {
    int total_car_count = 0;
    for(int i = 0; i < 365; i++) {
        total_car_count += dailydata[i].daily_car_count;
    }
    return total_car_count;
}

// Calculate the total KW energy production for the year.
double printTotalKwProfit(DailyData dailydata[365], RoadData roadData) {
    double total_kw = 0;
    for(int i = 0; i < 365; i++) {
        total_kw += dailydata[i].daily_car_count * roadData.kw_energy;
    }
    return total_kw;
}

// Calculate the total electric profit for the year.
double printTotalElectricProfit(DailyData dailydata[365]) {
    double total_profit = 0;
    for(int i = 0; i < 365; i++) {
        total_profit += dailydata[i].daily_electric_profit;
    }
    return total_profit;
}

// Write the daily calculated values, based on user input, to a text file.
void writeDailyDataToFile(DailyData dailydata[365], RoadData roadData) {
    FILE *file = fopen("dailyData.txt", "w");
    if(file == NULL) {
        printf("Unable to open dailyData.txt\n");
        return;
    }

    for(int i = 0; i < 365; i++) {
        fprintf(file, "Daily Car: %d Cars, Daily Electric Profit: %.2lf TL, Daily KW Cost: %.2lf TL, Calculated KW Energy: %.2lf KW \n", 
                dailydata[i].daily_car_count, 
                dailydata[i].daily_electric_profit, 
                dailydata[i].kw_cost, 
                roadData.kw_energy);
    }

    fclose(file);
}

int main() {
    RoadData roadData = getRoadData();
    printf("Calculated KW Energy: %.2lf\n", roadData.kw_energy);
    DailyData dailydata[365];
    assignRandomCarCount(dailydata);
    readPricesFromCSV(dailydata);
    calculateDailyElectricProfit(dailydata, roadData);
    printf("Total Car Count for the year: %d Cars\n", printTotalCarCount(dailydata));
    printf("Total KW Profit for the year: %.2lf Kw\n", printTotalKwProfit(dailydata, roadData));
    printf("Total Electric Profit for the year: %.2lf TL\n", printTotalElectricProfit(dailydata));
    writeDailyDataToFile(dailydata, roadData);

    return 0;
}
