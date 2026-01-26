#include "stdafx.h"
#include "Environment.h"

namespace app
{
	namespace actor
	{
		namespace
		{
			/** モデルを格納しているファイルのパスとモデルの拡張子 */
			const std::string MODEL_FILE_PATH = "Assets/modelData/stage/";
			const std::string MODEL_EXTENSION = ".tkm";
		}


		void Environment::InitModel(std::string path)
		{
			std::string fullPath = MODEL_FILE_PATH + path + MODEL_EXTENSION;
			m_modelRender.Init(fullPath.c_str());
			m_modelRender.SetTRS(m_transform.m_position, m_transform.m_rotation, m_transform.m_scale);
			m_modelRender.Update();
		}


		void Environment::Render(RenderContext& rc)
		{
			GetModelRender()->Draw(rc);
		}
	}
}
