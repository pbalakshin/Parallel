void swap(int *x, int *y) {
	int t = *x;
	*x = *y;
	// hardware interrupt
	*y = t;
}
void interrupt_handler() {
	int x = 1, y = 2;
	swap(&x, &y);
}