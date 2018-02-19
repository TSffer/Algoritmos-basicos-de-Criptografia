string get_file_contents(const char *filename)
{
  ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    return(string( (std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>() ));
  }
}

int inverso(int number, int modulo)
{
  int b = number;
  int a = modulo;

  int u , v , r , q , x , y , x_tmp , y_tmp;
  x = 1 , v = 1 , y = 0, u = 0;

  do{
    q = a/b;
    r = a%b;
    a = b; b = r;
    x_tmp = x; y_tmp = y;
    x = u; y = v;
    u = x_tmp - q*u;
    v = y_tmp - q*v;
  } while(b > 0);
  while(y < 0){
    y +=modulo;
  }
  return y;
}
