struct CameraData {
	float x; float y; float z;
	float pitch; float yaw; float roll;
	float fov;
};

/**
*  @brief Singleton class for a single camera in a scene.
* 
* 
*/
class Camera {
	private:
		
		struct CameraData data;


	public:
		
		Camera() {
			data = { 0.f,0.f,0.f,0.f,0.f,0.f,2.f };
		}

		struct CameraData GetData() {
			return data;
		}

		void SetData(struct CameraData newData) {
			data = newData;
		}
};
