// func, loops and condition

func Main() {
    bool is_work = true;
    float num = 0.5;
    while(is_work == true) {
        for(int i = 0; i > 10; i++ ) {
            print(i);
        }
        if(num >= 5.5) {
            is_work = false;
        }
        elif(num >= 1.5) {
            num += 0.5;
        }
        else {
            num += 1;
        }
    }
}

print("Main test");
Main();