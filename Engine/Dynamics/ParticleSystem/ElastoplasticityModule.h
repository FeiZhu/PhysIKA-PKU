#pragma once
#include "Framework/Framework/FieldVar.h"
#include "Framework/Framework/FieldArray.h"
#include "Framework/Topology/FieldNeighbor.h"
#include "Dynamics/ParticleSystem/ElasticityModule.h"

namespace Physika {

	template<typename TDataType>
	class ElastoplasticityModule : public ElasticityModule<TDataType>
	{
	public:
		typedef typename TDataType::Real Real;
		typedef typename TDataType::Coord Coord;
		typedef typename TDataType::Matrix Matrix;
		typedef TPair<TDataType> NPair;

		ElastoplasticityModule();
		~ElastoplasticityModule() override {};
		
		bool constrain() override;

		void applyPlasticity();

		void reconstructRestShape();

		void rotateRestShape();

		void setCohesion(Real c);
		void setFrictionAngle(Real phi);

		virtual void computeStiffness();

	protected:
		bool initializeImpl() override;

	private:
		inline Real computeA()
		{
			Real phi = m_phi.getValue();
			return (Real)6.0*m_c.getValue()*cos(phi) / (3.0f + sin(phi)) / sqrt(3.0f);
		}


		inline Real computeB()
		{
			Real phi = m_phi.getValue();
			return (Real)2.0f*sin(phi) / (3.0f + sin(phi)) / sqrt(3.0f);
		}

		VarField<Real> m_c;
		VarField<Real> m_phi;

		DeviceArray<bool> m_bYield;
		DeviceArray<Matrix> m_invF;
		DeviceArray<Real> m_yiled_I1;
		DeviceArray<Real> m_yield_J2;
		DeviceArray<Real> m_I1;

	};

#ifdef PRECISION_FLOAT
	template class ElastoplasticityModule<DataType3f>;
#else
	template class ElastoplasticityModule<DataType3d>;
#endif
}