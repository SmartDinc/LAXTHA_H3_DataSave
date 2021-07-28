extern "C" _declspec(dllimport) void ACQPLOT_DLL_Window_Size_Changed_Or_Data_Set_Changed(LPVOID lParam,CRect total_client,int unitbitmap_width_for_plot,int number_channel, int number_array_data, float data_y_amplitude,BOOL is_overlap,BOOL is_line,BOOL is_x_text,int number_x_text,float timeinterval_unitbitmap_width,int array_plot_mode);
extern "C" _declspec(dllimport) void ACQPLOT_DLL_Init_Array_Config(int number_channel,int number_array_data, float data_y_amplitude,BOOL is_overlap,BOOL is_line,int array_plot_mode);
extern "C" _declspec(dllimport) void ACQPLOT_DLL_Array_Datain_OneShot(float array_data[],unsigned size1, unsigned size2);
extern "C" _declspec(dllimport) void ACQPLOT_DLL_Array_Datain_Scroll(float array_data[],unsigned size1, unsigned size2);
extern "C" _declspec(dllimport) void ACQPLOT_DLL_Array_Datain_Strip(float array_data[],unsigned size1, unsigned size2);
extern "C" _declspec(dllimport) int ACQPLOT_DLL_Array_Draw_Box_Axis(CDC* pDC, BOOL is_box, BOOL is_x_axis, BOOL is_y_axis);
extern "C" _declspec(dllimport) void ACQPLOT_DLL_Init_OneShot_Config(LPVOID lParam,CRect plot_rect,int number_channel,float data_y_amplitude,BOOL is_overlap,BOOL is_line,int scroll_step,int plot_mode);
extern "C" _declspec(dllimport) void ACQPLOT_DLL_OneShot_DataIn_Real_Time_Plot(float oneshot_data[]);
extern "C" _declspec(dllimport) void ACQPLOT_DLL_Draw_Axis_Y_Text(CDC * pDC, CString text_array[], CString font_name);