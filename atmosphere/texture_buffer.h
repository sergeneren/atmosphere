
#ifndef __TEXTURE_BUFFER_H__
#define __TEXTURE_BUFFER_H__

#include "texture_types.h"
#include "driver_types.h"


struct TextureBuffer {

	cudaTextureObject_t m_delta_irradiance_texture;
	cudaTextureObject_t m_delta_rayleigh_scattering_texture;
	cudaTextureObject_t m_delta_mie_scattering_texture;
	cudaTextureObject_t m_delta_scattering_density_texture;
	cudaTextureObject_t m_delta_multiple_scattering_texture;

	cudaArray_t m_transmittance_array[2];
	cudaArray_t m_irradiance_array[2];
	cudaArray_t m_scattering_array[2];
	cudaArray_t m_optional_single_mie_scattering_array[2];
	
	TextureBuffer(bool half_precision);
	~TextureBuffer();
};

#endif