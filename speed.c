

int_16 Fuzzy_Table[13][13]= 
{ 
203,211,211,211,226,226,230,230,228,210,210,210,210,
209,221,221,221,238,238,241,241,237,231,231,231,227,
209,221,221,221,238,238,241,241,237,231,231,231,227,
209,221,221,221,238,238,241,241,237,231,231,231,227,
215,238,238,238,245,245,266,266,246,237,237,237,232,
215,238,238,238,245,245,266,266,246,237,237,237,232,
218,250,250,250,276,276,283,283,280,245,245,245,216,
218,250,250,250,276,276,283,283,280,245,245,245,216,
232,240,240,240,250,250,271,271,246,236,236,236,217,
226,230,230,230,236,236,239,239,236,214,214,214,208,
226,230,230,230,236,236,239,239,236,214,214,214,208,
226,230,230,230,236,236,239,239,236,214,214,214,208,
211,211,211,211,226,226,230,230,228,208,208,208,203
}  ;

int_16 get_speed_set(void) {
	int_16 E = 0, EC = 0;
	int_16 speed_target;
	static int_16 re_pos = 0, ek = 0, eck = 0;
	float ke = 400, kec = 10;
	ek = 2500 - row;
	eck = 2500 - row - re_pos;
	re_pos = ek;

	if (ek > 0) {

		E = (int_32)(ek / ke + 0.5);
	}
	else {

		E = (int_32)(ek / ke - 0.5);
	}
	//将E的论域转换到模糊控制器的论域
	if (E > 6)
		E = 6;
	else if (E < -6)
		E = -6;
	if (eck > 0) {

		EC = (int_16)(eck / kec + 0.5);
	}
	else {

		EC = (int_16)(eck / kec - 0.5);
	}//将EC的论域转换到模糊控制器的论域
	if (EC > 6)
		EC = 6;
	else if (EC < -6)
		EC = -6;

	speed_target = (int_16)(Fuzzy_Table[E + 6][EC + 6]);
	return speed_target ;
}

int speed_control(void)
{
	int i;
	speed_set=get_speed_set();//设置车速                  
	
	//设置PID参数
	kp_motor=33;
	ki_motor=0.038;
	kd_motor=0.04;

	for(i=0;i<9;i++)
		error[i]=error[i+1];
	error[9]=speed_set-speed;	

	de=kp_motor*(error[9]-error[8])+ki_motor*error[9]-kd_motor*(speed_save[9]-2*speed_save[8]+speed_save[7]);
	pwm1 = pwm1_old+de;
  	
  	speed_set_old=speed_set;
  	pwm1_old=pwm1; 
  	return pwm1;//输出PWM波
}
