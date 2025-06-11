//-------------------------------------------------------------------
//�v���C��
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Player.h"
#include  "Task_Map2D.h"
#include  "Task_Effect00.h"
#include "Task_Shot00.h"
#include "Task_Shot01.h"

namespace  Player
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//���\�[�X�̏�����
	bool  Resource::Initialize()
	{
		this->img = DG::Image::Create("./data/image/HitTest.bmp");
		return true;
	}
	//-------------------------------------------------------------------
	//���\�[�X�̉��
	bool  Resource::Finalize()
	{
		this->img.reset();
		return true;
	}
	//-------------------------------------------------------------------
	//�u�������v�^�X�N�������ɂP�񂾂��s������
	bool  Object::Initialize()
	{
		//�X�[�p�[�N���X������
		__super::Initialize(defGroupName, defName, true);
		//���\�[�X�N���X����or���\�[�X���L
		this->res = Resource::Create();

		//���f�[�^������
		this->render2D_Priority[1] = 0.5f;
		this->controller = ge->in1;
		this->pos.x = 0;
		this->pos.y = 0;
		this->hitBase = ML::Box2D(-15, -24, 30, 48);
		this->angle_LR = Angle_LR::Right;
		
		//���^�X�N�̐���

		return  true;
	}
	//-------------------------------------------------------------------
	//�u�I���v�^�X�N���Ŏ��ɂP�񂾂��s������
	bool  Object::Finalize()
	{
		//���f�[�^���^�X�N���


		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//�������p���^�X�N�̐���
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//�u�X�V�v�P�t���[�����ɍs������
	void  Object::UpDate()
	{
		ML::Vec2  est(0, 0);
		if (this->controller) {
			auto  inp = this->controller->GetState();
			if (inp.LStick.BL.on) { est.x -= 3; this->angle_LR = Angle_LR::Left;	}
			if (inp.LStick.BR.on) { est.x += 3; this->angle_LR = Angle_LR::Right;	}
			if (inp.LStick.BU.on) { est.y -= 3; }
			if (inp.LStick.BD.on) { est.y += 3; }

			//�e������
			if (inp.B3.down) {
				//�e�𐶐�
				auto  shot = Shot00::Object::Create(true);
				shot->pos = this->pos;
				if (this->angle_LR == Angle_LR::Right) {
					shot->moveVec = ML::Vec2(8, 0);
				}
				else {
					shot->moveVec = ML::Vec2(-8, 0);
				}
			}
			if (inp.B4.down) {
				//�e�𐶐�
				auto  shot = Shot01::Object::Create(true);
				shot->pos = this->pos;
				if (this->angle_LR == Angle_LR::Right) {
					shot->moveVec = ML::Vec2(5, -6);
				}
				else {
					shot->moveVec = ML::Vec2(-5, -6);
				}
			}
		}
		this->CheckMove(est);
		//�����ڐG����
		this->hitFlag = this->CheckFoot();

		//�J�����̈ʒu���Ē���
		{
			//�v���C������ʂ̉����ɒu�����i����͉�ʒ����j
			int  px = ge->camera2D.w / 2;
			int  py = ge->camera2D.h / 2;
			//�v���C������ʒ����ɒu�������̃J�����̍�����W�����߂�
			int  cpx = int(this->pos.x) - px;
			int  cpy = int(this->pos.y) - py;
			//�J�����̍��W���X�V
			ge->camera2D.x = cpx;
			ge->camera2D.y = cpy;
			if (auto   map = ge->GetTask<Map2D::Object>(Map2D::defGroupName, Map2D::defName)) {
				map->AdjustCameraPos();
			}
		}
	}
	//-------------------------------------------------------------------
	//�u�Q�c�`��v�P�t���[�����ɍs������
	void  Object::Render2D_AF()
	{
		ML::Box2D  draw = this->hitBase.OffsetCopy(this->pos);
		ML::Box2D  src(0, 0, 100, 100);
		//�X�N���[���Ή�
		draw.Offset(-ge->camera2D.x, -ge->camera2D.y);


		this->res->img->Draw(draw, src);
	}

	//������������������������������������������������������������������������������������
	//�ȉ��͊�{�I�ɕύX�s�v�ȃ��\�b�h
	//������������������������������������������������������������������������������������
	//-------------------------------------------------------------------
	//�^�X�N��������
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//�Q�[���G���W���ɓo�^
				//�i���\�b�h�����ςȂ̂͋��o�[�W�����̃R�s�[�ɂ��o�O��������邽��
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//�C�j�V�����C�Y�Ɏ��s������Kill
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
	//���\�[�X�N���X�̐���
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