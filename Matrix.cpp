#include "Matrix.h"

Matrix::Matrix(int n)
{
	this->n = n;
	data = new float *[n];
	for (int i = 0; i < n; i++)
	{
		data[i] = new float[n];
	}
}

Matrix ::Matrix(const Matrix &x)
{
	this->n = x.n;
	this->data = new float *[n];
	for (int i = 0; i < n; i++)
	{
		data[i] = new float[n];
	}
	for (int i = 0; i < x.n; i++)
	{
		for (int j = 0; j < x.n; j++)
		{
			data[i][j] = x(i, j);
		}
	}
}

Matrix ::~Matrix()
{
	for (int i = 0; i < n; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}

Matrix Matrix::IdentityMatrix(){
	for(int i=0;i<n;i++){
		for(int j = 0;j<n;j++){
			this->data[i][j] = 0;
			if (i == j){
				this->data[i][j] = 1;
			}
		}
	}
	return *this;
}

const Matrix Matrix::operator*(const Matrix &x)
{
	Matrix k(x.n);
	for (int i = 0; i < x.n; i++)
	{
		for (int j = 0; j < x.n; j++)
		{
			k(i, j) = 0;
			for (int l = 0; l < n; l++)
			{
				k(i, j) += data[i][l] * x(l, j);
			}
		}
	}
	return k;
}

Matrix Matrix::operator=(const Matrix &x)
{
	if (this != &x)
	{
		for (int i = 0; i < n; i++)
		{
			delete[] data[i];
		}
		delete[] data;
		this->n = x.n;
		data = new float *[n];
		for (int i = 0; i < n; i++)
		{
			data[i] = new float[n];
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				data[i][j] = x(i, j);
	}
	return *this;
}

float &Matrix::operator()(int i, int j) const
{
	return data[i][j];
}

const Matrix Matrix::Transpose(){
	Matrix k(this->n);
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			k(i,j) = this->data[j][i];
		}
	}
	return k;
}
