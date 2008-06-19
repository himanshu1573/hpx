//  Copyright (c) 2007-2008 Hartmut Kaiser
//  Copyright (c) 2007 Richard D Guidry Jr
//  Copyright (c) 2007 Alexandre (aka Alex) TABBAL
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PARCELSET_PARCEL_MAR_26_2008_1051AM)
#define HPX_PARCELSET_PARCEL_MAR_26_2008_1051AM

#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

#include <hpx/exception.hpp>
#include <hpx/components/action.hpp>
#include <hpx/components/continuation.hpp>
#include <hpx/runtime/naming/name.hpp>
#include <hpx/runtime/naming/address.hpp>

///////////////////////////////////////////////////////////////////////////////
//  parcel serialization format version
#define HPX_PARCEL_VERSION 0x40

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace parcelset
{
    ///////////////////////////////////////////////////////////////////////////
    typedef naming::id_type parcel_id;

    parcel_id const no_parcel_id = parcel_id();
    parcel_id const invalid_parcel_id = naming::invalid_id;
    
    ///////////////////////////////////////////////////////////////////////////
    class parcel
    {
    public:
        parcel() 
          : tag_(0), destination_id_(0), source_id_(), action_(), 
            continuation_(), start_time_(0)
        {
        }

        parcel(naming::id_type apply_to)
          : tag_(0), destination_id_(apply_to), source_id_(0), action_(), 
            continuation_(), start_time_(0)
        {
        }

        parcel(naming::id_type apply_to, components::action_base* act)
          : tag_(0), destination_id_(apply_to), source_id_(0), action_(act), 
            continuation_(), start_time_(0)
        {
        }

        parcel(naming::id_type apply_to, components::action_base* act, 
               components::continuation* do_after) 
          : tag_(0), destination_id_(apply_to), source_id_(0), action_(act), 
            continuation_(do_after), start_time_(0)
        {
        }

        parcel(naming::id_type apply_to, components::action_base* act, 
               components::continuation_type do_after) 
          : tag_(0), destination_id_(apply_to), source_id_(0), action_(act), 
            continuation_(do_after), start_time_(0)
        {
        }

        ~parcel()
        {
        }

        // default copy constructor is ok    
        // default assignment operator is ok

        components::action_type get_action() const 
        {
            return action_;
        }

        components::continuation_type get_continuation() const 
        {
            return continuation_;
        }

        /// get and set the parcel id
        parcel_id const& get_parcel_id() const 
        {
            return tag_;
        }
        void set_parcel_id(parcel_id const& id) 
        {
            tag_ = id;
        }

        /// get and set the source locality/component id
        naming::id_type get_source() const
        {
            return source_id_;
        }
        void set_source(naming::id_type source_id)
        {
            source_id_ = source_id;
        }

        /// get and set the destination id
        void set_destination(naming::id_type dest)
        {
            destination_id_ = dest;
        }
        naming::id_type get_destination() const
        {
            return destination_id_;
        }

        /// get and set the destination address
        void set_destination_addr(naming::address const& addr)
        {
            destination_addr_ = addr;
        }
        naming::address const& get_destination_addr() const
        {
            return destination_addr_;
        }

        void set_start_time(double starttime)
        {
            start_time_ = starttime;
        }
        double get_start_time() const
        {
            return start_time_;
        }

    private:
        // serialization support
        friend class boost::serialization::access;

        template<class Archive>
        void save(Archive & ar, const unsigned int version) const;

        template<class Archive>
        void load(Archive & ar, const unsigned int version);

        BOOST_SERIALIZATION_SPLIT_MEMBER()

    private:
        parcel_id tag_;   
        naming::id_type destination_id_;
        naming::address destination_addr_;
        naming::id_type source_id_;
        components::action_type action_;
        components::continuation_type continuation_;
        double start_time_;
    };

///////////////////////////////////////////////////////////////////////////////
}}

///////////////////////////////////////////////////////////////////////////////
// this is the current version of the parcel serialization format
// this definition needs to be in the global namespace
BOOST_CLASS_VERSION(hpx::parcelset::parcel, HPX_PARCEL_VERSION)
BOOST_CLASS_TRACKING(hpx::parcelset::parcel, boost::serialization::track_never)

#endif
