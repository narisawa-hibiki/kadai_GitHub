//-------------------------------------------------------------------
//プレイヤ
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Player.h"
#include  "Task_Map2D.h"

namespace  Player
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//リソースの初期化
	bool  Resource::Initialize()
	{
		this->img = DG::Image::Create("./data/image/星-01.png");
		this->font = DG::Font::Create("ＭＳ ゴシック", 8, 16);
		return true;
	}
	//-------------------------------------------------------------------
	//リソースの解放
	bool  Resource::Finalize()
	{
		this->img.reset();
		this->font.reset();
		return true;
	}
	//-------------------------------------------------------------------
	//「初期化」タスク生成時に１回だけ行う処理
	bool  Object::Initialize()
	{
		//スーパークラス初期化
		__super::Initialize(defGroupName, defName, true);
		//リソースクラス生成orリソース共有
		this->res = Resource::Create();

		//★データ初期化
		this->render2D_Priority[1] = 0.5f;
		this->controller = ge->in1;
		this->moveStep = 3;

		//★タスクの生成

		return  true;
	}
	//-------------------------------------------------------------------
	//「終了」タスク消滅時に１回だけ行う処理
	bool  Object::Finalize()
	{
		//★データ＆タスク解放


		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//★引き継ぎタスクの生成
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
		auto  inp = this->controller->GetState();
		//移動
		if (inp.LStick.BL.down) { this->pos.x -= 1; }
		if (inp.LStick.BR.down) { this->pos.x += 1; }
		if (inp.LStick.BU.down) { this->pos.y -= 1; }
		if (inp.LStick.BD.down) { this->pos.y += 1; }
		//カメラ移動
		if (inp.RStick.BL.on) { ge->camera2D.x -= 1; }
		if (inp.RStick.BR.on) { ge->camera2D.x += 1; }
		if (inp.RStick.BU.on) { ge->camera2D.y -= 1; }
		if (inp.RStick.BD.on) { ge->camera2D.y += 1; }
		//歩数変更
		if (inp.B1.down) { this->moveStep = min(this->moveStep + 1, 15); }
		if (inp.B2.down) { this->moveStep = max(this->moveStep - 1, 1); }
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
		ML::Box2D  draw(0, 0, 16, 16);
		ML::Box2D  src(0, 0, 256, 256);
		draw.Offset(this->pos * 16);
		//スクロール対応
		draw.Offset(-ge->camera2D.x, -ge->camera2D.y);
		this->res->img->Draw(draw, src);

		//
		ML::Box2D   textDraw(300, 0, 200, 32);
		stringstream  ss;
		ss << "位置(" << this->pos.x << "," << this->pos.y << ")\n" << "移動歩数" << this->moveStep;
		string  str;
		str = ss.str();
		this->res->font->DrawF(textDraw, str, DG::Font::FRAME::x4);
	}

	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//以下は基本的に変更不要なメソッド
	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//-------------------------------------------------------------------
	//タスク生成窓口
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//ゲームエンジンに登録
				//（メソッド名が変なのは旧バージョンのコピーによるバグを回避するため
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//イニシャライズに失敗したらKill
			}
			return  ob;
		}
		return nullptr;
	}
	//-------------------------------------------------------------------
	bool  Object::B_Initialize()
	{
		return  this->Initialize();
	}
	//-------------------------------------------------------------------
	Object::~Object() { this->B_Finalize(); }
	bool  Object::B_Finalize()
	{
		auto  rtv = this->Finalize();
		return  rtv;
	}
	//-------------------------------------------------------------------
	Object::Object() {	}
	//-------------------------------------------------------------------
	//リソースクラスの生成
	Resource::SP  Resource::Create()
	{
		if (auto sp = instance.lock()) {
			return sp;
		}
		else {
			sp = Resource::SP(new  Resource());
			if (sp) {
				sp->Initialize();
				instance = sp;
			}
			return sp;
		}
	}
	//-------------------------------------------------------------------
	Resource::Resource() {}
	//-------------------------------------------------------------------
	Resource::~Resource() { this->Finalize(); }
}