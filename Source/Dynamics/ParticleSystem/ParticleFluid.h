#pragma once
#include "ParticleSystem.h"
#include "ParticleEmitter.h"

namespace PhysIKA
{
	/*!
	*	\class	ParticleFluid
	*	\brief	Position-based fluids.
	*
	*	This class implements a position-based fluid solver.
	*	Refer to Macklin and Muller's "Position Based Fluids" for details
	*
	*/
	template<typename TDataType>
	class ParticleFluid : public ParticleSystem<TDataType>
	{
		DECLARE_CLASS_1(ParticleFluid, TDataType)
	public:
		typedef typename TDataType::Real Real;
		typedef typename TDataType::Coord Coord;

		ParticleFluid(std::string name = "default");
		virtual ~ParticleFluid();

		void advance(Real dt) override;

		bool addEmitter(std::shared_ptr<ParticleEmitter<TDataType>> child);

		DEF_NODE_PORTS(ParticleEmitters, ParticleEmitter<TDataType>, "Particle Emitters");

	private:
		std::shared_ptr<ParticleEmitter<TDataType>> m_ParticleEmitter = NULL;
	};

#ifdef PRECISION_FLOAT
	template class ParticleFluid<DataType3f>;
#else
	template class ParticleFluid<DataType3d>;
#endif
}