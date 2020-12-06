class object
{
public:
	float x,y;
	int model_id,skip;
	float height,width;
	float velocity;
	float o,theta;
	float w;
	float acceleration;
	float mass;
	object()
	{
		model_id=2;
		w=0.01;
		theta=0;
		o=0;
		x=200;
		y=300;
	}
	object(int i)
	{
		model_id=i;
		w=0.1;
		theta=0;
		o=0;
		x=200;
		y=800;
	}
	void rotate(float i);
	void anim();
	void run();
	void set_dimentions();
};

void object::set_dimentions()
{
	width=models[model_id].width;
	height=models[model_id].height;
}
void object::rotate(float i)
{
	theta=i;
}

void object::anim()
{
	direct_draw_to_page_trans(direct_page5,model_id,x,y-cam.y,theta+1.57);
}

void object::run()
{
	x+=velocity*cos(o);
	y+=velocity*sin(o);
	theta+=w;
	if(theta>6.28)
		theta=0;
	direct_draw_to_page_trans(direct_page5,model_id,x,y-cam.y,theta+1.57);//theta+1.57);
}