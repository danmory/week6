#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


void sort(int arr1[], int arr2[], int N){
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (arr1[j] > arr1[j + 1]) {
                swap(&arr1[j], &arr1[j + 1]);
                swap(&arr2[j], &arr2[j + 1]);
            }
        }
    }
}

/* FINDING WAITING, COMPLETION AND TURNAROUND TIMES */
void findTimes(int burstTimes[], int arrivalTimes[], int waitingTimes[], int completionTimes[], int turnaroundTimes[], int N){
    sort(arrivalTimes, burstTimes, N);
    int isDone[N];
    for (int i = 0; i < N; ++i) {
        completionTimes[i] = arrivalTimes[i] + burstTimes[i];
        for (int j = 0; j < i; ++j) {
            if (arrivalTimes[i] < completionTimes[j]) {
                if (burstTimes[i] >= burstTimes[j]) {
                    if (completionTimes[i] < completionTimes[j] + burstTimes[i]) {
                        completionTimes[i] = completionTimes[j] + burstTimes[i];
                    }
                } else {
                    completionTimes[j] += burstTimes[i];
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        turnaroundTimes[i] = completionTimes[i] - arrivalTimes[i];
        waitingTimes[i] = turnaroundTimes[i] - burstTimes[i];
    }

}

/* AVERAGE VALUES */
float findAverageValue(int arr[], int N){
    int totalValue = 0;
    for (int i = 0; i < N; ++i) {
        totalValue += arr[i];
    }
    return (float)totalValue/N;
}

/* PRINT TABLE WITH RESULTS */
void print(int completionTimes[], int turnaroundTimes[], int waitingTimes[], float avTurnaroundTime, float avWaitingTime, int N){
    printf("id\t\tct\t\ttat\t\twt\n");
    for (int i = 0; i < N; ++i) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i, completionTimes[i], turnaroundTimes[i], waitingTimes[i]);
    }

    printf("Average turnaround time: %f \n", avTurnaroundTime);
    printf("Average waiting time: %f \n", avWaitingTime);
}

int main() {
    /* GETTING INPUT DATA*/
    int N;
    printf("Number of processes: ");
    scanf("%d", &N);
    printf("\n");
    if (N == 0){
        exit(0);
    }
    int arrivalTimes[N];
    int burstTimes[N];
    for (int i = 0; i < N; ++i) {
        printf("#%d process arrival time: ", i);
        scanf("%d", &arrivalTimes[i]);
        printf("#%d process burst time: ", i);
        scanf("%d", &burstTimes[i]);
    }

    /* TO FIND OUT: */
    int completionTimes[N];
    int turnaroundTimes[N];
    int waitingTimes[N];
    float avTurnaroundTime;
    float avWaitingTime;

    findTimes(burstTimes, arrivalTimes, waitingTimes, completionTimes, turnaroundTimes, N);

    avTurnaroundTime = findAverageValue(turnaroundTimes, N);
    avWaitingTime = findAverageValue(waitingTimes, N);

    print(completionTimes, turnaroundTimes, waitingTimes, avTurnaroundTime, avWaitingTime, N);

    return 0;
}
