void enter_profile(LPCTSTR func,LPCTSTR file,int line);
void leave_profile(LPCTSTR func,LPCTSTR file,int line);

#ifdef _DEBUG
#define E_P(x) enter_profile(x,__FILE__,__LINE__)
#define L_P(x) leave_profile(x,__FILE__,__LINE__)
#else
#define E_P(x)
#define L_P(x)
#endif