#ifndef RUNNER_H__
#define RUNNER_H__

namespace Runner
{
    template<typename VectorType>
    class Animation
    {
        void setStartValue(const VectorType& aValue);
        const VectorType& aValue getStartValue() const;
        
        void setEndValue(const VectorType& aValue);
        const VectorType& aValue getEndValue() const;

        void animate(/*startTime, currentTime*/);
        void update();

        void setDuration(/*duration*/);
        // duration getDuration() const;
    };
}

#endif /*RUNNER_H__*/