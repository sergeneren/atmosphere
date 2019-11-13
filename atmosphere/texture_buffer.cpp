

#include "atmosphere/texture_buffer.h"
#include "atmosphere/constants.h"
#include "cuda_runtime.h"


TextureBuffer::TextureBuffer(bool half_precision) {

	// Allocate arrays on gpu 
	cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float4>();
	cudaChannelFormatDesc channelDescHalf = cudaCreateChannelDescHalf4();


	cudaMallocArray(&m_transmittance_array[0], half_precision ? &channelDescHalf : &channelDesc, TRANSMITTANCE_TEXTURE_WIDTH, TRANSMITTANCE_TEXTURE_HEIGHT);
	cudaMallocArray(&m_transmittance_array[1], half_precision ? &channelDescHalf : &channelDesc, TRANSMITTANCE_TEXTURE_WIDTH, TRANSMITTANCE_TEXTURE_HEIGHT);

	cudaMallocArray(&m_irradiance_array[0], half_precision ? &channelDescHalf : &channelDesc, IRRADIANCE_TEXTURE_WIDTH, IRRADIANCE_TEXTURE_HEIGHT);
	cudaMallocArray(&m_irradiance_array[1], half_precision ? &channelDescHalf : &channelDesc, IRRADIANCE_TEXTURE_WIDTH, IRRADIANCE_TEXTURE_HEIGHT);

	cudaExtent scattering_array_size;
	scattering_array_size.width = SCATTERING_TEXTURE_WIDTH;
	scattering_array_size.height = SCATTERING_TEXTURE_HEIGHT;
	scattering_array_size.depth = SCATTERING_TEXTURE_DEPTH;

	cudaMalloc3DArray(&m_scattering_array[0], half_precision ? &channelDescHalf : &channelDesc, scattering_array_size);
	cudaMalloc3DArray(&m_scattering_array[1], half_precision ? &channelDescHalf : &channelDesc, scattering_array_size);

	cudaMalloc3DArray(&m_optional_single_mie_scattering_array[0], half_precision ? &channelDescHalf : &channelDesc, scattering_array_size);
	cudaMalloc3DArray(&m_optional_single_mie_scattering_array[1], half_precision ? &channelDescHalf : &channelDesc, scattering_array_size);

}


TextureBuffer::~TextureBuffer() {

	// Free GPU resources 

	cudaFree(&m_delta_irradiance_texture);
	cudaFree(&m_delta_rayleigh_scattering_texture);
	cudaFree(&m_delta_mie_scattering_texture);
	cudaFree(&m_delta_scattering_density_texture);
	cudaFree(&m_delta_multiple_scattering_texture);


	cudaFree(&m_transmittance_array[0]);
	cudaFree(&m_transmittance_array[1]);

	cudaFree(&m_irradiance_array[0]);
	cudaFree(&m_irradiance_array[1]);

	cudaFree(&m_scattering_array[0]);
	cudaFree(&m_scattering_array[1]);

	cudaFree(&m_optional_single_mie_scattering_array[0]);
	cudaFree(&m_optional_single_mie_scattering_array[1]);

}