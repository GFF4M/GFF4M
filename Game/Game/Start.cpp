#include "stdafx.h"
#include "Start.h"

SC_Start::SC_Start()
{
}


SC_Start::~SC_Start()
{
}

void SC_Start::Start()
{

	haikeiTex.Load("Assets/Sprite/siro.png");
	newGameTex.Load("Assets/Sprite/NEW.png");
	contenyuTex.Load("Assets/Sprite/cc.png");
	TitleTex.Load("Assets/Sprite/Title.png");

	haikei.Init(&haikeiTex);
	contenyu.Init(&contenyuTex);
	newGame.Init(&newGameTex);
	Title.Init(&TitleTex);


	haikei.SetSize(haikeiMaxSize);
	contenyu.SetSize(contenyuMaxSize);
	newGame.SetSize(newGameMaxSize);
	Title.SetSize(TitleMaxSize);


	haikei.SetPivot({ 0.5f, 0.5f });
	contenyu.SetPivot({ 0.5f,0.5f });
	newGame.SetPivot({ 0.5f, 0.5f });
	Title.SetPivot({ 0.5f,0.5f });

	haikei.SetPosition(haikeiPos);
	contenyu.SetPosition(contenyuPos);
	newGame.SetPosition(newGamePos);
	Title.SetPosition(TitlePos);

	/*soundSource.Init("Assets/modelData/bgm_maoudamashii_piano25.wav");
	soundSource.Play(true);*/
}

void SC_Start::Update()
{
	/*soundSource.Update();*/
}

void SC_Start::PostRender(CRenderContext& renderContext)
{
	haikei.Draw(renderContext);
	newGame.Draw(renderContext);
	contenyu.Draw(renderContext);
	Title.Draw(renderContext);
}


void SC_Start::Delete()
{
	DeleteGO(this);
}