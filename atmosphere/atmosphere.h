//--------------------------------------------------------------------------------
//
//	Redistribution and use in source and binary forms, with or without
//	modification, are permitted provided that the following conditions are met :
//
//	*Redistributions of source code must retain the above copyright notice, this
//	list of conditions and the following disclaimer.
//
//	* Redistributions in binary form must reproduce the above copyright notice,
//	this list of conditions and the following disclaimer in the documentation
//	and/or other materials provided with the distribution.
//	
//	* Neither the name of the copyright holder nor the names of its
//	contributors may be used to endorse or promote products derived from
//	this software without specific prior written permission.
//	
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//	DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//	DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//	OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Copyright(c) 2019, Sergen Eren
// All rights reserved.
//----------------------------------------------------------------------------------
// 
//	Version 1.0: Sergen Eren, 11/11/2019
//
// File: This is the header file for atmosphere class that implements 
//		 bruneton model sky in cuda. This file contains device side function 
//		 definitions and host side function declerations
//
//-----------------------------------------------


#ifndef  __ATMOSPHERE_H__
#define __ATMOSPHERE_H__


#include <cuda.h>
#include "texture_types.h"

#include <vector>

#include "atmosphere/definitions.h"
#include "atmosphere/texture_buffer.h"
#include "atmosphere/constants.h"

enum atmosphere_error_t {

	ATMO_INIT_ERR,
	ATMO_INIT_FUNC_ERR,
	ATMO_RECOMPUTE_ERR,
	ATMO_FILL_TEX_ERR,
	ATMO_NO_ERR

};

class atmosphere {


private:

	#define kLambdaR 680.0
	#define kLambdaG 550.0
	#define kLambdaB 440.0

	#define kLambdaMin 360
	#define kLambdaMax 830



public:
	
	atmosphere();
	~atmosphere();

	atmosphere_error_t init(bool , bool);
	atmosphere_error_t init_functions(CUmodule &cuda_module);
	atmosphere_error_t precompute(float azimuth, float elevation, float exposure);
	atmosphere_error_t fill_transmittance_texture();
	atmosphere_error_t fill_scattering_texture();
	atmosphere_error_t fill_irradiance_texture();


public:

	std::vector<double> m_wave_lengths;
	std::vector<double> m_solar_irradiance;
	
	double m_sun_angular_radius;
	double m_bottom_radius;
	double m_top_radius;
	
	DensityProfileLayer* m_rayleigh_density;
	std::vector<double> m_rayleigh_scattering;
	
	DensityProfileLayer* m_mie_density;
	std::vector<double> m_mie_scattering;
	std::vector<double> m_mie_extinction;
	double m_mie_phase_function_g;
	
	std::vector<DensityProfileLayer*> m_absorption_density;
	std::vector<double> m_absorption_extinction;
	
	std::vector<double> m_ground_albedo;

	double m_max_sun_zenith_angle;
	double m_length_unit_in_meters;
	LUMINANCE m_use_luminance;
	inline int num_precomputed_wavelengths() { return m_use_luminance == LUMINANCE::PRECOMPUTED ? 15 : 3; }
	bool m_combine_scattering_textures;
	bool m_half_precision = false;

	TextureBuffer *m_texture_buffer;
	AtmosphereTextures atmosphere_textures;
	AtmosphereParameters atmosphere_parameters;

	CUfunction *transmittance_function;
	CUfunction *direct_irradiance_function;
	CUfunction *indirect_irradiance_function;
	CUfunction *multiple_scattering_function;
	CUfunction *scattering_density_function;
	CUfunction *single_scattering_function;

	float3 *transmittance_buffer;
	float4 *scattering_buffer;
	float3 *irradiance_buffer;
	   	 
	   
};

#endif // ! __ATMOSPHERE_H__
