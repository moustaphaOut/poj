#include <stdio.h>
#include <math.h>

int main(){
    double Vs, R, C;
    int n;

    scanf("%lf %lf %lf %d", &Vs, &R, &C, &n);
    while(n--){
        double omega;
        scanf("%lf", &omega);
        
        double CRw = C * R * omega;
        double phi = atan(1.0 / CRw);
        
        printf("%.3lf\n", CRw * Vs * sin(phi));
    }

    return 0;
}
