void adjustdown(int *in,int begin0,int end0)
{
	int i=begin0,j;
	while(i<=end0)
	{
		if(2*i+1<=end0)
		{
			j=2*i+1;
			if(2*i+2<=end0&&in[j]<in[2*i+2])
				j=2*i+2;
			if(in[j]>in[i])
			{
				int temp=in[i];
				in[i]=in[j];
				in[j]=temp;
				i=j;
			}
			else
				break;
		}
		else
			break;
	}
}
void HeapSort(int *in,int length)
{
	for(int i=length/2;i>=0;--i)
		adjustdown(in,i,length-1);
	for(int i=length-1;i>=0;--i)
	{
		int temp=in[i];
		in[i]=in[0];
		in[0]=temp;
		adjustdown(in,0,i-1);
	}
	
}
