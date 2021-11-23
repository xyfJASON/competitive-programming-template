#define gc()(is==it?it=(is=in)+fread(in,1,Q,stdin),(is==it?EOF:*is++):*is++)
const int Q=(1«24)+1;
char in[Q],*is=in,*it=in,c;
void read(long long &n){
  for(n=0;(c=gc())<'0'||c>'9';);
  for(;c<='9'&&c>='0';c=gc())n=n*10+c-48;
}