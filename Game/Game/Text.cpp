#include "stdafx.h"
#include "Text.h"

namespace {

	const CVector2 haikeiPos = { 0.0f, 0.0f };
	const CVector2 haikeiMaxSize = { 1500.0f, 1000.0f };
	const CVector2 newGameMaxSize = { 230.0f, 80.0f };
	const CVector2 newGamePos = { 0.0f, -100.0f };
	const CVector2 contenyuPos = { 0.0f,-280.0f };
	const CVector2 contenyuMaxSize = { 230.0f,80.0f };
	const CVector2 TitlePos = { 0.0f,150.0f };
	const CVector2 TitleMaxSize = { 700.0f,200.0f };
}

Text::Text()
{
}


Text::~Text()
{
}

void Text::Start()
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

void Text::Update()
{
	/*soundSource.Update();*/
}

void Text::PostRender(CRenderContext& renderContext)
{
	haikei.Draw(renderContext);
	newGame.Draw(renderContext);
	contenyu.Draw(renderContext);
	Title.Draw(renderContext);
}