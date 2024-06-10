long_double calc_triangle(long_double x1,long_double y1,long_double x2,long_double y2,long_double x3,long_double y3){
    return abs((x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2))/2.0);
}
