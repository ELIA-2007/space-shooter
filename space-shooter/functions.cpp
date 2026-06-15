float mapValue(float a, float b, float A, float B, float x) {
	if (a != b) return A + (B - A) * ((x - a) / (b - a)); else return 0;
}