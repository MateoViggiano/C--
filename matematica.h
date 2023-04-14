long double _pot(double base,int exponente){
	double n=1;
	if(exponente<0){
		exponente*=-1;
		base=1/base;
	}
	for(int i=0;i<exponente;i++){
		n*=base;
	}
	return n;
}
long double exp(double n,long long p=10000){		//La mas exacta
	double sumatoria=1,productoria=1;
	for(double i=1;i<=p;i++){
		productoria*=n/i;
		sumatoria+=productoria;
	}
	return sumatoria;
}
long double ln(double x,int p=1000000){
	long double n=0;
	if(x<0.5){
		for(int i=1;i<=p;i++){
			n+=(_pot(-1,i-1)*_pot(x-1,i))/i;		//n+=pot(-1,i)*(pot(x-1.,i+1.)/(i+1));
		}
	}
	else if(x<1500){
		for(long long i=1;i<p;i++){
			n+=(1./i)*_pot((x-1)/x,i);
		}
	}
	else{
		n=10;
		for(int i=2;i<=p;i++){	
			if(exp(n)>x)
				while(exp(n)>x)
					n-=n/i;
			else if(exp(n)<x)
				while(exp(n)<x)
					n+=n/i;
			else return n;
		}
	}
	return n;
}
long double pot(double base,double exponente){
	return exp(exponente*ln(base));	
}
long long fact(int n){
	int a=1;
	for(int i=1;i<=n;i++){
		a*=i;
	}
	return a;
}
long long fibo(int n){
	if(n==0) return 0;
	long long a=0,b=1,c=1;
	for(int i=1;i<n;i++){
		c=a+b;
		a=b;
		b=c;
	}
	return c;
}