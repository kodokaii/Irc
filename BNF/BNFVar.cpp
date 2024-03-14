/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFVar.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/14 00:42:21 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFVar.hpp"

BNFVar::BNFVar(std::string const &name):	BNFParser(name),
											rule(NULL)
{
}

BNFVar::BNFVar(std::string const &name, BNFParser const &rule):	BNFParser(name),
																rule(rule.clone())
{
}

BNFVar::BNFVar(BNFVar const &other):	BNFParser(other),
										rule(other.rule->clone())
{
}

BNFVar::~BNFVar(void)
{
	delete this->rule;
}

std::string BNFVar::getFormatName(void) const
{
    return (this->name);
}

void		BNFVar::reset(void)
{
	this->rule->reset();
	this->value = this->rule->getValue();
	this->errorPos = this->rule->getErrorPos();
}

BNFParser	*BNFVar::clone(void) const
{
	return (new BNFVar(*this));
}

ssize_t		BNFVar::parse(std::string const &str, size_t start)
{
	ssize_t	res;

	res = this->rule->parse(str, start);
	this->value = this->rule->getValue();
	this->errorPos = this->rule->getErrorPos();
	return(res);
}

BNFAlts     BNFVar::operator|(BNFParser const &other) const
{
	return (BNFAlts(this->getFormatName() + '|' + other.getFormatName(), 2, this, &other));
}

BNFAlts      BNFVar::operator|(std::string const &str) const
{
    BNFString   tmp(str);

    return (BNFAlts(this->getFormatName() + '|' + tmp.getFormatName(), 2, this, &tmp));
}

BNFAlts      BNFVar::operator|(char c) const
{
    BNFChar   tmp(c);

    return (BNFAlts(this->getFormatName() + '|' + tmp.getFormatName(), 2, this, &tmp));
}

BNFCat      BNFVar::operator&(BNFParser const &other) const
{
	return (BNFCat(this->getFormatName() + '&' + other.getFormatName(), 2, this, &other));
}

BNFCat      BNFVar::operator&(std::string const &str) const
{
    BNFString   tmp(str);

    return (BNFCat(this->getFormatName() + '&' + tmp.getFormatName(), 2, this, &tmp));
}

BNFCat      BNFVar::operator&(char c) const
{
    BNFChar   tmp(c);

    return (BNFCat(this->getFormatName() + '&' + tmp.getFormatName(), 2, this, &tmp));
}

BNFRep      BNFVar::operator+(size_t max) const
{
	return (BNFRep(this->getFormatName() + '+' + kdo::itoa(max), *this, 0, max));
}

BNFRep		BNFVar::operator-(size_t min) const
{
	return (BNFRep(this->getFormatName() + '-' + kdo::itoa(min), *this, min, BNF_INFINI));
}

BNFFind		BNFVar::operator[](std::string const &name) const
{
	BNFFind	res;

	res.merge((*this->rule)[name]);
	res.pushParent(*this);
	if (this->name == name)
		res.push_back(BNFInher(*this));
	return (res);
}

BNFVar	&BNFVar::operator=(BNFVar const &other)
{
	delete this->rule;
	this->value = other.getValue();
	this->errorPos = other.getErrorPos();
	this->rule = other.rule->clone();
	return (*this);
}

BNFVar	&BNFVar::operator=(BNFParser const &other)
{
	delete this->rule;
	this->value = other.getValue();
	this->errorPos = other.getErrorPos();
	this->rule = other.clone();
	return (*this);
}
