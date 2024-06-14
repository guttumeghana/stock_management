#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STOCK 10
#define DAY 10
#define FLT_MAX 5000


struct StockData {
    char symbol[10]; 
    float open;      
    float high;      
    float low;       
    float close;     
    int volume;      
}sd;

struct StockData stockData[STOCK][DAY]; 

//FIRST QUESTION ANSWER
// Function to calculate the percentage change in stock price
float calculatePercentageChange(struct StockData s[STOCK][DAY],char symbol[], int startDay, int endDay) {
    int stockNumber,result,change;
    for(int i=0;i<STOCK;i++)
    {
        if(strcmp(symbol,s[i][0].symbol)==0){
            stockNumber=i;
        }
        else
        {
            printf("invalid");
        }
    }
    change=s[stockNumber][startDay].open-s[stockNumber][endDay].close;
    result=(change/s[stockNumber][startDay].open)*100;
    return result;
}


//SECOND QUESTION ANSWER
// Function to sort stocks by volume and close prices
void sortStocksByVolumeAndClose(struct StockData s[STOCK][DAY],int day) {
    int small=s[0][day].volume;
    int smallest=s[0][day].close;
    for(int i=1;i<STOCK;i++)
    {
        if(small>s[i][day].volume)
        {
            int temp1=small;
            small=s[i][day].volume;
            s[i][day].volume=temp1;
        }
        else if(small==s[i][day].volume)
        {
            if(smallest>s[i][day].close)
            {
                int temp2=smallest;
                smallest=s[i][day].close;
                s[i][day].close=temp2;
            }
        }
    }
}

//THIRD QUESTION ANSWER
// Function to calculate profit/loss of stocks for two different dates
float calculateProfitLoss(struct StockData s[STOCK][DAY],char symbol[], int buyDay, int sellDay) {
    float buyPrice = -1.0;  
    float sellPrice = -1.0; 
    for (int i = 0; i < STOCK; i++) {
        if (strcmp(s[i][0].symbol, symbol) == 0) {
            if (s[i][buyDay].close > 0) {
                buyPrice = s[i][buyDay].close;   
            } else {
                return -1.0; 
            }
            if (s[i][sellDay].close > 0) {
                sellPrice = s[i][sellDay].close; 
            } else {
                return -1.0; 
            }
            float profitLoss = ((sellPrice - buyPrice) / buyPrice) * 100.0;
            return profitLoss;
        }
    }
    
    return -1.0;
}

//FOURTH QUESTION ANSWER
// Function to find the highest performing stock for a specified duration
char* findHighestPerformingStock(struct StockData s[STOCK][DAY],int startDay, int endDay) {
    char* bestStockSymbol = NULL;
    float bestGain = -1.0; 
    for (int i = 0; i < 10; i++) {
        float startPrice = s[i][startDay].close;
        float endPrice = s[i][endDay].close;

        if (startPrice > 0 && endPrice > 0) {
            float gain = ((endPrice - startPrice) / startPrice) * 100.0;

            if (gain > bestGain) {
                bestGain = gain;
                bestStockSymbol = s[i][0].symbol;
            }
        }
    }
    return bestStockSymbol;
}

//FIFTH QUESTION ANSWER
// Function to find the lowest performing stock for a specified duration
char* findLowestPerformingStock(struct StockData s[STOCK][DAY],int startDay, int endDay) {
    char* worstStockSymbol = NULL;
    float worstGain = FLT_MAX; 
    for (int i = 0; i < 10; i++) {
        float startPrice = s[i][startDay].close;
        float endPrice = s[i][endDay].close;

        if (startPrice > 0 && endPrice > 0) {
            float gain = ((endPrice - startPrice) / startPrice) * 100.0;

            if (gain < worstGain) {
                worstGain = gain;
                worstStockSymbol = s[i][0].symbol;
            }
        }
    }
    return worstStockSymbol;
}

//SIXTH QUESTION ANSWER
// Function to list all stocks by increasing overall performance
void listStocksByPerformance(struct StockData s[STOCK][DAY], int startDay, int endDay) {
    float overallPerformance[10] = {0.0};
    for (int i = 0; i < 10; i++) {
        for (int day = startDay + 1; day <= endDay; day++) {
            float prevClose = s[i][day - 1].close;
            float currentClose = s[i][day].close;
            float volume = s[i][day].volume;

            if (prevClose > 0 && currentClose > 0) {
                float dailyChange = ((currentClose - prevClose) / prevClose) * 100.0;
                overallPerformance[i] += dailyChange * volume;
            }
        }
    }
    int sortedIndices[10];
    for (int i = 0; i < STOCK; i++) {
        sortedIndices[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (overallPerformance[sortedIndices[i]] > overallPerformance[sortedIndices[j]]) {
                int temp = sortedIndices[i];
                sortedIndices[i] = sortedIndices[j];
                sortedIndices[j] = temp;
            }
        }
    }
    // Print stocks in increasing order of overall performance
    printf("Stocks in increasing order of overall performance:\n");
    for (int i = 0; i < STOCK; i++) {
        int index = sortedIndices[i];
        printf("Stock: %s, Overall Performance: %.2f\n", s[index][0].symbol, overallPerformance[index]);
    }
}

//SEVENTH QUESTION ANSWER
// Function to find the average of average values of all stocks for a specified duration
float findAverageOfAverageValues(struct StockData s[STOCK][DAY], int startDay, int endDay) {
    float totalWeightedAverage = 0.0;
    int totalStocks = STOCK;
    for (int i = 0; i < totalStocks; i++) {
        float stockWeightedAverage = 0.0;
        
        for (int day = startDay; day <= endDay; day++) {
            float stockPrice = s[i][day].close;
            float stockVolume = s[i][day].volume;
            
            if (stockPrice > 0) {
                stockWeightedAverage += (stockPrice * stockVolume);
            }
        }

        totalWeightedAverage += stockWeightedAverage;
    }
    float averageOfAverageValues = totalWeightedAverage / (totalStocks * (endDay - startDay + 1));
    return averageOfAverageValues;
}


int main() {
    printf("Enter the required values\n");
    int startDay, endDay;

    for (int i = 0; i < STOCK; i++) {
        
        for (int j = 0; j < DAY; j++) {
            
            stockData[i][j].open = 100.0 -(i*2) +(j*3);
            stockData[i][j].high= 145.0 + (j*1.1);
            stockData[i][j].low = 81.0 + j;
            stockData[i][j].close = 105.0 -( j*3) ;
            stockData[i][j].volume = 10000;
        }
    }


    char stock1[50]="AARTIIND";
    for(int i=0;i<STOCK;i++){
   strcpy(stockData[i][0].symbol,stock1);
    }
   char stock2[50]="ABCAPITAL";
   for(int i=0;i<STOCK;i++){
   strcpy(stockData[i][1].symbol,stock2);
    }
   char stock3[50]="PNB";
   for(int i=0;i<STOCK;i++){
   strcpy(stockData[i][2].symbol,stock3);
    }
   char stock4[50]="DLF";
   for(int i=0;i<STOCK;i++){
   strcpy(stockData[i][3].symbol,stock4);
    }
    char stock5[50]="GODREJEF";
    for(int i=0;i<STOCK;i++){
   strcpy(stockData[i][4].symbol,stock5);
    }
   char stock6[50]="INFY";
   for(int i=0;i<STOCK;i++){
   strcpy(stockData[i][5].symbol,stock6);
    }
    char stock7[50]="HDFCLIFE";
    for(int i=0;i<STOCK;i++){
   strcpy(stockData[i][6].symbol,stock7);
    }
    char stock8[50]="IOC";
    for(int i=0;i<STOCK;i++){
   strcpy(stockData[i][7].symbol,stock8);
    }
    char stock9[50]="ONGC";
    for(int i=0;i<STOCK;i++){
   strcpy(stockData[i][8].symbol,stock9);
    }
     char stock10[50]="IRCTC";
     for(int i=0;i<STOCK;i++){
   strcpy(stockData[i][9].symbol,stock10);
    }

    printf("Enter the startDay: ");
    scanf("%d", &startDay);
    printf("Enter the endDay: ");
    scanf("%d", &endDay);
    calculatePercentageChange(stockData, stockData[STOCK][DAY].symbol, startDay, endDay);
    sortStocksByVolumeAndClose(stockData, startDay);
    calculateProfitLoss(stockData, stockData[STOCK][DAY].symbol, startDay, endDay);
    findHighestPerformingStock(stockData, startDay, endDay);
    findLowestPerformingStock(stockData, startDay, endDay);
    listStocksByPerformance(stockData, startDay, endDay);
    findAverageOfAverageValues(stockData, startDay, endDay);
    return 0;
}