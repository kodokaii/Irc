/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BNFCat.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/12 17:21:25 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BNFCat.hpp"

BNFCat::BNFCat(std::string const &name, t_uint count, ...): BNFParser(name)
{
	va_list	argList;

	va_start(argList, count);
	while (count--)
		this->rules.push_back(va_arg(argList, BNFParser *)->clone());
	va_end(argList);
}

BNFCat::BNFCat(std::vector<BNFParser *> rules, std::string const &name):	BNFParser(name)
{
	std::vector<BNFParser *>::const_iterator	cr;

	for (cr = rules.begin(); cr != rules.end(); cr++)
		this->rules.push_back((*cr)->clone());
}

BNFCat::BNFCat(BNFCat const &other):	BNFParser(other)
{
	std::vector<BNFParser *>::const_iterator	cr;

	for (cr = other.rules.begin(); cr != other.rules.end(); cr++)
		this->rules.push_back((*cr)->clone());
}

BNFCat::~BNFCat(void)
{
	std::vector<BNFParser *>::iterator	cr;

	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		delete *cr;
}

void		BNFCat::reset(void)
{
	std::vector<BNFParser *>::iterator	cr;

	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		(*cr)->reset();
	this->errorPos = BNF_ERROR_POS_UNINITIALIZED;
	this->value.clear();
}

BNFParser	*BNFCat::clone(void) const
{
	return (new BNFCat(*this));
}

ssize_t		BNFCat::parse(std::string const &str, size_t start)
{
	std::vector<BNFParser *>::iterator	cr;
	ssize_t	finalLen(0);
	ssize_t	len;

	this->value.clear();
	for (cr = this->rules.begin(); cr != this->rules.end() && start + finalLen < str.length(); cr++)
	{
		len = (*cr)->parse(str, start + finalLen);
		if (len == BNF_PARSE_ERROR)
			break;
		this->value += (*cr)->getValue();
		finalLen += len;	
	}
	if (cr != this->rules.end())
	{
		while (cr != this->rules.end())
			(*cr++)->reset();
		this->errorPos = start + finalLen;
		return (BNF_PARSE_ERROR);
	}
	this->errorPos = BNF_ERROR_POS_NONE;
	return (finalLen);
}

BNFFind		*BNFCat::operator[](std::string const &name) const
{
	std::vector<BNFParser *>::const_iterator	cr;
	BNFFind										*finalRes(new BNFFind());
	BNFFind										*res;

	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
	{
		res = (**cr)[name];
		finalRes->merge(*res);
		delete res;
	}
	finalRes->pushParent(*this);
	if (this->name == name)
		finalRes->pushBack(BNFInher(*this));
	return (finalRes);
}

BNFCat	&BNFCat::operator=(BNFCat const &other)
{
	std::vector<BNFParser *>::const_iterator	cr;

	for (cr = this->rules.begin(); cr != this->rules.end(); cr++)
		delete *cr;
	this->rules.clear();
	*static_cast<BNFParser *>(this) = other;
	for (cr = other.rules.begin(); cr != other.rules.end(); cr++)
		this->rules.push_back((*cr)->clone());
	return (*this);
}
