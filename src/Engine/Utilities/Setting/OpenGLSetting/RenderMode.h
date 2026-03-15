#ifndef RENEDER_MODE_H
#define RENEDER_MODE_H

#include <glad/glad.h>

namespace GLSetting {
	enum RenderMode {
		Fill = GL_FILL,
		Line = GL_LINE
	};

	inline const RenderMode DefaultRenderMode = RenderMode::Fill;
	inline RenderMode SelectedRenderMode = DefaultRenderMode;

	inline void changeRenderMode() {
		if (SelectedRenderMode == RenderMode::Fill) {
			SelectedRenderMode = RenderMode::Line;
		}
		else if (SelectedRenderMode == RenderMode::Line) {
			SelectedRenderMode = RenderMode::Fill;
		}

		glPolygonMode(GL_FRONT_AND_BACK, SelectedRenderMode);
	}
}

#endif
