int main(void){
    int i;
    int a;
    int j;
    int ret = 0;

    a = 2;
    j = 0;
    while (j < 100){
        i = 0;
        while(i<1000000) {
            a = a * i;
            i = i + 1;
        }
        j = j + 1;
    }
    return ret;
}
