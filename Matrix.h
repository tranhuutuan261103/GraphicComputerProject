#ifndef Matrix_h
#define Matrix_h

class Matrix{
	private:
		float** data;
		int n;
	public:
		Matrix(int n = 4);
		Matrix(const Matrix &x);
		~Matrix();
		void printfMatrix();
		Matrix IdentityMatrix();
		const Matrix operator*(const Matrix &x);
		Matrix operator=(const Matrix &x);
		float &operator()(int, int) const;
		const Matrix Transpose();
};

#endif
