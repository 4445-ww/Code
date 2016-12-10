// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能并不是按逆时针方向给出。
double area(point vertex[], int numberOfVertex)
{
	double areaOfPolygon = 0.0;

	for (int i = 0; i < numberOfVertex; i++)
	{
		int j = (i + 1) % numberOfVertex;
		areaOfPolygon += (vertex[i].x * vertex[j].y - vertex[j].x * vertex[i].y);
	}

	return fabs(areaOfPolygon / 2.0);
}