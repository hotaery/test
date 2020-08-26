void __attribute__((always_inline)) fn() {
    int a = 1;
    int b = 2;
    int c = a + b;
}

int main() {
    fn();
}